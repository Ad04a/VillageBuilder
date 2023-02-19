// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkSystem/VillageManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/GameplayModeBase.h"
#include "AI/Villager/VillagerAIController.h"


// Sets default values
AVillageManager::AVillageManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
}

// Called when the game starts or when spawned
void AVillageManager::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(World) == false"));
		return;
	}
	AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	GameMode->SetVillage(this);
	float SpawnTime = FMath::RandRange(MinTimeBetweenSpawn, MaxTimeBetweenSpawn);
	GetWorldTimerManager().SetTimer(SpawnHandle, this, &AVillageManager::TimedSpawn, SpawnTime, false, MinTimeBetweenSpawn);
}

void AVillageManager::Init(FVillageManagerLoadInfoStruct InLoadInfo)
{
	SetActorTransform(InLoadInfo.Transform);
	
	for (FVillagerLoadInfoStruct VillagerInfo : InLoadInfo.PassingVillagers)
	{
		SpawnVillager(FVector(), VillagerInfo);
	}
	
	
	for (FVillagerLoadInfoStruct VillagerInfo : InLoadInfo.Villagers)
	{
		AddVillagerToColony(SpawnVillager(FVector(), VillagerInfo));
	}
}

FVillageManagerLoadInfoStruct AVillageManager::GetSaveInfo()
{
	FVillageManagerLoadInfoStruct SaveInfo;
	TArray<AVillager*> PassingVillagersCopy = PassingVillagers;
	TArray<AVillager*> VillagersCopy = Villagers;
	TArray<FVillagerLoadInfoStruct> PassingVillagerInfos;
	TArray<FVillagerLoadInfoStruct> VillagerInfos;
	for (AVillager* Villager : PassingVillagersCopy)
	{
		PassingVillagerInfos.Add(Villager->GetSaveInfo());
	}
	for (AVillager* Villager : VillagersCopy)
	{
		VillagerInfos.Add(Villager->GetSaveInfo());
	}
	SaveInfo.PassingVillagers = PassingVillagerInfos;
	SaveInfo.Villagers		  = VillagerInfos;
	SaveInfo.Transform		  = GetActorTransform();
	return SaveInfo;
}

AVillager* AVillageManager::SpawnVillager(FVector Position, FVillagerLoadInfoStruct LoadInfo)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageManager::SpawnVillager IsValid(World) == false"));
		return nullptr;
	}

	FVector Location = Position;
	FRotator Rotation = FRotator(0, 0, 0);
	FActorSpawnParameters Params;

	if (LoadInfo != FVillagerLoadInfoStruct())
	{
		Location = LoadInfo.Transform.GetLocation();
		Rotation = LoadInfo.Transform.Rotator();
	}

	AVillager* Villager = World->SpawnActor<AVillager>(VillagerClass, Location, Rotation, Params);

	if (IsValid(Villager) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageManager::SpawnVillager IsValid(Player) == false"));
		return nullptr;
	}

	Villager->Init(LoadInfo);
	PassingVillagers.Add(Villager);
	OnStateUpdated.Broadcast();
	return Villager;
}

void AVillageManager::TimedSpawn()
{
	AddVillagerToColony(SpawnVillager(FVector(FMath::RandRange(-500,500), FMath::RandRange(-500, 500), 100)));
	float SpawnTime = FMath::RandRange(MinTimeBetweenSpawn, MaxTimeBetweenSpawn);
	GetWorldTimerManager().SetTimer(SpawnHandle, this, &AVillageManager::TimedSpawn, SpawnTime, false);
}

void AVillageManager::PauseTimedSpawn()
{
	GetWorldTimerManager().PauseTimer(SpawnHandle);
}

void AVillageManager::UnPauseTimedSpawn()
{
	GetWorldTimerManager().UnPauseTimer(SpawnHandle);
}

void AVillageManager::OnVillagerDeath(AVillager* Villager)
{
	Villagers.Remove(Villager);
	ABaseWorkStation* Station = GetWorkPlaceFor(Villager);
	if (Station != nullptr)
	{
		ManageEmployment(Station, nullptr);
	}
	Villager->Destroy();
}

void AVillageManager::AddVillagerToColony(AVillager* Villager)
{
	PassingVillagers.Remove(Villager);
	Villagers.Add(Villager);
	OnStateUpdated.Broadcast();

	Villager->OnDeath.AddDynamic(this, &AVillageManager::OnVillagerDeath);
	OnVillagersUpdated.ExecuteIfBound(Villagers);
}

AVillager* AVillageManager::GetWorkerAt(ABaseWorkStation* WorkStation)
{
	return *WorkStations.Find(WorkStation);
}

ABaseWorkStation* AVillageManager::GetWorkPlaceFor(AVillager* Worker)
{
	for (TPair<ABaseWorkStation*, AVillager*>Station : WorkStations)
	{
		if (Station.Value == Worker)
		{
			return Station.Key;
		}
	}
	return nullptr;
}

void AVillageManager::ManageEmployment(ABaseWorkStation* WorkStation, AVillager* Worker)
{
	if (IsValid(WorkStation) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageManager::ManageEmployment IsValid(WorkStation) == false"));
		return;
	}

	ApplyJobBehavior("Unemployed", GetWorkerAt(WorkStation));

	if (GetWorkPlaceFor(Worker) != nullptr)
	{
		WorkStations.Add(GetWorkPlaceFor(Worker), nullptr);
	}

	WorkStations.Add(WorkStation, Worker);

	ApplyJobBehavior(WorkStation->GetClass()->GetFName(), Worker);
	
	OnStateUpdated.Broadcast();
	OnVillagersUpdated.ExecuteIfBound(Villagers);
	
}

void AVillageManager::AddWorkStationToColony(ABaseWorkStation* WorkStation)
{
	PlacedBuildings.Add(WorkStation);
	OnStateUpdated.Broadcast();
	WorkStation->OnStartedConstruction.BindDynamic(this, &AVillageManager::AknowedgeStartedConstruction);
}

void AVillageManager::AknowedgeStartedConstruction(ABaseWorkStation* WorkStation)
{
	PlacedBuildings.Remove(WorkStation);
	WorkStation->OnStartedConstruction.Unbind();
	UnderConstruction.Add(WorkStation);
	OnStateUpdated.Broadcast();
	WorkStation->OnBuildingReady.BindDynamic(this, &AVillageManager::AknowedgeFinishedBuilding);
}

void AVillageManager::AknowedgeFinishedBuilding(ABaseWorkStation* WorkStation)
{
	UnderConstruction.Remove(WorkStation);
	WorkStation->OnBuildingReady.Unbind();
	WorkStations.Add(WorkStation, nullptr);
	OnStateUpdated.Broadcast();
}

void AVillageManager::ApplyJobBehavior(FName StationName, AVillager* Worker)
{
	if (IsValid(Worker) == false)
	{
		return;
	}
	AVillagerAIController* WorkerController = Cast<AVillagerAIController>(Worker->GetController());
	if (IsValid(WorkerController) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageManager::ManageEmployment IsValid(WorkerController) == false"));
		return;
	}
	if (WorkerBehaviors.Contains(StationName) == false)
	{
		if (IsValid(BehaviorDataTable) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("AVillageManager::ManageEmployment IsValid(DataTable)==false"));
			return;
		}

		FWorkStationData* BehaviorData = BehaviorDataTable->FindRow<FWorkStationData>(StationName, "");

		if (BehaviorData == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AVillageManager::ManageEmployment BehaviorData == nullptr "));
			return;
		}

		WorkerBehaviors.Add(StationName, BehaviorData->BehaviorTree);
	}
	WorkerController->SetBehavior(*WorkerBehaviors.Find(StationName));
}

ABaseWorkStation* AVillageManager::GetFirstForConstructing()
{
	if (UnderConstruction.IsEmpty() == true)
	{
		return nullptr;
	}
	return UnderConstruction[0];
}
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

	FString FilePath = FPaths::ProjectContentDir() + "/NonAssets/"  + NamesFile;
	FFileHelper::LoadFileToStringArray(Names, *FilePath);

	AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	GameMode->SetVillage(this);
	float SpawnTime = FMath::RandRange(MinTimeBetweenSpawn, MaxTimeBetweenSpawn);
	GetWorldTimerManager().SetTimer(SpawnHandle, this, &AVillageManager::TimedSpawn, SpawnTime, false, MinTimeBetweenSpawn);
}

void AVillageManager::Init(FVillageManagerLoadInfoStruct InLoadInfo)
{
	bCanGenerateSaves = false;
	SetActorTransform(InLoadInfo.Transform);
	
	CurrentID = InLoadInfo.CurrentID;

	for (FVillagerLoadInfoStruct VillagerInfo : InLoadInfo.PassingVillagers)
	{
		SpawnVillager(FVector(), VillagerInfo);
	}
	
	for (FVillagerLoadInfoStruct VillagerInfo : InLoadInfo.Villagers)
	{
		AddVillagerToColony(SpawnVillager(FVector(), VillagerInfo));
	}

	for (FWorkStationInfoStruct StationInfo : InLoadInfo.WorkStations)
	{
		ABaseWorkStation* Station = ABaseWorkStation::CreateInstance(this, StationInfo);
		AddWorkStationToColony(Station);
		Station->Init(StationInfo);
	}

	for (TPair<int, int> Contract : InLoadInfo.WorkPlaces)
	{
		ABaseWorkStation* TempWorkStation = nullptr;
		for (TPair<ABaseWorkStation*, int> Station : WorkStations)
		{
			if (Station.Key->ID == Contract.Key)
			{
				TempWorkStation = Station.Key;
				break;
			}
		}
		int TempIndex = 0;
		for (AVillager* Villager : Villagers)
		{
			if (Villager->ID == Contract.Value)
			{
				TempIndex = Villagers.IndexOfByKey(Villager);
				break;
			}
		}
		ManageEmployment(TempWorkStation, TempIndex);
	}

	bCanGenerateSaves = true;
	GenerateSave();
}

FVillageManagerLoadInfoStruct AVillageManager::GetSaveInfo()
{
	FVillageManagerLoadInfoStruct SaveInfo;
	SaveInfo.Transform = GetActorTransform();
	//----------------VillagersSAveInfo------------------------
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
	//----------------WorkStatiionSAveInfo----------------------
	TArray<FWorkStationInfoStruct> WorkStationsInfos;
	for (ABaseWorkStation* Building : PlacedBuildings)
	{
		WorkStationsInfos.Add(Building->GetSaveInfo());
	}
	for (ABaseWorkStation* Construct : UnderConstruction)
	{
		WorkStationsInfos.Add(Construct->GetSaveInfo());
	}
	TArray<ABaseWorkStation*> Stations;
	WorkStations.GenerateKeyArray(Stations);
	for (TPair<ABaseWorkStation*, int> Station : WorkStations)
	{
		WorkStationsInfos.Add(Station.Key->GetSaveInfo());
		SaveInfo.WorkPlaces.Add(Station.Key->ID, Station.Value);
	}
	SaveInfo.WorkStations = WorkStationsInfos;
	SaveInfo.CurrentID = CurrentID;

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
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	if (LoadInfo != FVillagerLoadInfoStruct())
	{
		Location = LoadInfo.Transform.GetLocation();
		Rotation = LoadInfo.Transform.Rotator();
	}

	AVillager* Villager = World->SpawnActor<AVillager>(VillagerClass, Location, Rotation, Params);

	if (IsValid(Villager) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageManager::SpawnVillager IsValid(Villager) == false"));
		return nullptr;
	}
	FString Name = "";
	if (LoadInfo.Name == "Name")
	{
		int32 RandomIndex = FMath::RandRange(0, Names.Num() - 1);
		Name = Names[RandomIndex];
	}
	Villager->Init(LoadInfo, Name);
	if (Villager->ID == 0)
	{
		Villager->ID = CurrentID;
		CurrentID += 1;
	}
	Villager->SetProfession(EProfessions::Passing);
	PassingVillagers.Add(Villager);
	GenerateSave();
	return Villager;
}

void AVillageManager::TimedSpawn()
{
	SpawnVillager(GetActorLocation() + FVector(FMath::RandRange(-Range, Range), FMath::RandRange(-Range, Range), 100));
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
	ABaseWorkStation* Station = GetWorkPlaceFor(Villager->ID);
	if (Station != nullptr)
	{
		ManageEmployment(Station, -1);
	}
	OnVillagersUpdated.ExecuteIfBound(Villagers);
	Villager->Destroy();

	VillagerRequests.Remove(Villager->ID);
	SendRequests();
}

void AVillageManager::AddVillagerToColony(AVillager* Villager)
{
	if (Villager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AVillageManager::AddVillagerToColony IsValid(Villager) == false"));
		return;
	}

	PassingVillagers.Remove(Villager);
	Villagers.Add(Villager);
	Villager->SetProfession(EProfessions::Unemployed);
	ApplyJobBehavior(EProfessions::Unemployed, Villager);
	Villager->OnDeath.AddDynamic(this, &AVillageManager::OnVillagerDeath);
	OnVillagersUpdated.ExecuteIfBound(Villagers);
	GenerateSave();
}

AVillager* AVillageManager::GetVillagerByID(unsigned int ID)
{
	for (AVillager* Villager : Villagers)
	{
		if (Villager->ID == ID)
		{
			return Villager;
		}
	}
	return nullptr;
}

AVillager* AVillageManager::GetWorkerAt(ABaseWorkStation* WorkStation)
{
	int WorkerID = *WorkStations.Find(WorkStation);
	for (AVillager* Villager : Villagers)
	{
		if (Villager->ID == WorkerID)
		{
			return Villager;
		}
	}
	return nullptr;
}

ABaseWorkStation* AVillageManager::GetWorkPlaceFor(unsigned int WorkerID)
{
	for (TPair<ABaseWorkStation*, unsigned int>Station : WorkStations)
	{
		if (Station.Value == WorkerID)
		{
			return Station.Key;
		}
	}
	return nullptr;
}

void AVillageManager::ManageEmployment(ABaseWorkStation* WorkStation, int WorkerIndex)
{
	VillagerRequests.Remove(WorkerIndex);
	if (IsValid(WorkStation) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageManager::ManageEmployment IsValid(WorkStation) == false"));
		return;
	}
	if (Villagers.IsValidIndex(WorkerIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("AVillageManager::ManageEmployment IsValid(VIllager) == false"));
		return;
	}
	unsigned int WorkerID = Villagers[WorkerIndex]->ID;
	bool bWorksHere = false;
	if (IsValid(GetWorkerAt(WorkStation)) == true)
	{
		bWorksHere = (GetWorkerAt(WorkStation)->ID == WorkerID);
	}
	ApplyJobBehavior(EProfessions::Unemployed, GetWorkerAt(WorkStation));
	if (IsValid(GetWorkerAt(WorkStation)) == true)
	{
		GetWorkerAt(WorkStation)->SetProfession(EProfessions::Unemployed);
	}

	if (GetWorkPlaceFor(WorkerID) != nullptr)
	{
		WorkStations.Add(GetWorkPlaceFor(WorkerID), 0);
	}
	if (bWorksHere == false)
	{
		WorkStations.Add(WorkStation, WorkerID);
		ApplyJobBehavior(WorkStation->GetProfession(), GetWorkerAt(WorkStation));
		GetWorkerAt(WorkStation)->SetProfession(WorkStation->GetProfession());

	}
	OnVillagersUpdated.ExecuteIfBound(Villagers);
	GenerateSave();
}

void AVillageManager::AddWorkStationToColony(ABaseWorkStation* WorkStation)
{
	PlacedBuildings.Add(WorkStation);
	WorkStation->OnStartedConstruction.AddUniqueDynamic(this, &AVillageManager::AknowedgeStartedConstruction);
	if (WorkStation->ID == 0)
	{
		WorkStation->ID = CurrentID++;
	}
	
	GenerateSave();
}

void AVillageManager::AknowedgeStartedConstruction(bool State, ABaseWorkStation* WorkStation)
{
	if (State == false)
	{
		UnderConstruction.Remove(WorkStation);
		WorkStation->OnBuildingReady.Unbind();
		AddWorkStationToColony(WorkStation);
		return;
	}
	PlacedBuildings.Remove(WorkStation);
	UnderConstruction.Add(WorkStation);
	WorkStation->OnBuildingReady.BindDynamic(this, &AVillageManager::AknowedgeFinishedBuilding);
	GenerateSave();
}

void AVillageManager::AknowedgeFinishedBuilding(ABaseWorkStation* WorkStation)
{
	UnderConstruction.Remove(WorkStation);
	WorkStation->OnStartedConstruction.RemoveDynamic(this, &AVillageManager::AknowedgeStartedConstruction);
	WorkStation->OnBuildingReady.Unbind();
	WorkStations.Add(WorkStation, 0);
	GenerateSave();
}

void AVillageManager::ApplyJobBehavior(EProfessions Profession, AVillager* Worker)
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
	if (WorkerBehaviors.Contains(Profession) == false)
	{
		if (IsValid(BehaviorDataTable) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("AVillageManager::ManageEmployment IsValid(DataTable)==false"));
			return;
		}

		FProfessionBehaviorData* BehaviorData = BehaviorDataTable->FindRow<FProfessionBehaviorData>(UEnum::GetValueAsName(Profession), "");

		if (BehaviorData == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AVillageManager::ManageEmployment BehaviorData == nullptr "));
			return;
		}

		WorkerBehaviors.Add(Profession, BehaviorData->BehaviorTree);
		WorkerMaterials.Add(Profession, BehaviorData->Material);
	}
	WorkerController->SetBehavior(*WorkerBehaviors.Find(Profession));
	Worker->GetMesh()->SetMaterial(0, *WorkerMaterials.Find(Profession));
}

ABaseWorkStation* AVillageManager::GetFirstForConstructing()
{
	if (UnderConstruction.IsEmpty() == true)
	{
		return nullptr;
	}
	return UnderConstruction[0];
}

void AVillageManager::GenerateSave()
{
	if (bCanGenerateSaves == false)
	{
		return;
	}
	OnStateUpdated.Broadcast();
}

TArray<ABaseWorkStation*> AVillageManager::GetWorkStations()
{
	TArray<ABaseWorkStation*> Stations;
	WorkStations.GenerateKeyArray(Stations);
	return Stations;
}

void AVillageManager::CommitRequest(TArray<TSubclassOf<class AItem>> Classes, AVillager* Villager, bool IsFull)
{
	FRequest Request;
	Request.Villager = Villager;
	Request.WorkStation = GetWorkPlaceFor(Villager->ID);
	Request.IsFull = IsFull;
	Request.Items = Classes;

	if (VillagerRequests.Contains(Villager->ID) == true)
	{
		FRequest CurrentRequest = *VillagerRequests.Find(Villager->ID);

		if (Request == CurrentRequest)
		{
			return;
		}
	}

	VillagerRequests.Emplace(Villager->ID, Request);

	SendRequests();
}

void AVillageManager::SendRequests()
{
	TArray<FRequest> Requests;
	VillagerRequests.GenerateValueArray(Requests);
	OnRequestsUpdated.Broadcast(Requests);
}

FRequest AVillageManager::GetFirstRequest()
{
	FRequest RequestToGet;
	for (TPair<unsigned int, FRequest> Request : VillagerRequests)
	{
		if (Request.Value.Items.IsEmpty() == false && IsValid(Request.Value.WorkStation) == true)
		{
			return Request.Value;
		}
	}
	return RequestToGet;
}

void AVillageManager::BreakDataLinks_Implementation()
{

}

FText AVillageManager::DisplayDataLinkText_Implementation()
{
	return FText::FromString("Manage Colony");
}
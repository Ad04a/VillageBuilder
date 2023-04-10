// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkSystem/BaseWorkStation.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Items/Item.h"
#include "Characters/VillageMayor.h"

ABaseWorkStation* ABaseWorkStation::CreateInstance(UObject* WorldContext, FWorkStationInfoStruct InLoadInfo)
{
	UWorld* World = WorldContext->GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AItem::CreateInstance IsValid(World) == false"));
		return nullptr;
	}
	if (InLoadInfo == FWorkStationInfoStruct())
	{
		return nullptr;
	}
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ABaseWorkStation* WorkStation = World->SpawnActor<ABaseWorkStation>(InLoadInfo.WorkStationClass, FVector(0, 0, 1000), FRotator(0, 0, 0), Params);
	return WorkStation;
}

ABaseWorkStation::ABaseWorkStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
	BuildingComponent = CreateDefaultSubobject<UBuildingClusterComponent>(TEXT("BuildingComponent"));
	BuildingComponent->SetupAttachment(MeshComponent);
	BuildingComponent->OnBuildingFinisehd.AddDynamic(this, &ABaseWorkStation::SetIsBuilt);
	BuildingComponent->OnBuildStarted.AddDynamic(this, &ABaseWorkStation::SetIsConstructing);

	StorageComponent = CreateDefaultSubobject<UStorageComponent>(TEXT("Storage"));
}

// Called when the game starts or when spawned
void ABaseWorkStation::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(StationDataTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ABaseWorkStation::LoadFromDataTable() IsValid(StationDataTable) == false from %s"), *GetClass()->GetName());
		return;
	}

	FWorkStationData* StationData = StationDataTable->FindRow<FWorkStationData>(GetClass()->GetFName(), "");

	if (StationData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ABaseWorkStation::LoadFromDataTable() FWorkStationData == nullptr from %s"), *GetClass()->GetName());
		return;
	}

	DisplayName    = StationData->DisplayName;
	TraitModifiers = StationData->TraitModifiers;
	Profession     = StationData->Profession;

	StorageComponent->Init();

}

void ABaseWorkStation::Init(FWorkStationInfoStruct InLoadInfo )
{
	SetActorTransform(InLoadInfo.Transform);
	BuildingComponent->Init(InLoadInfo.BuildingClusterInfo);
	StorageComponent->Init(InLoadInfo.InventoryInfo);
	ID = InLoadInfo.ID;
}

FWorkStationInfoStruct ABaseWorkStation::GetSaveInfo()
{
	FWorkStationInfoStruct SaveInfo;
	SaveInfo.Transform		     = GetActorTransform();
	SaveInfo.WorkStationClass    = GetClass();
	SaveInfo.BuildingClusterInfo = BuildingComponent->GetSaveInfo();
	SaveInfo.InventoryInfo		 = StorageComponent->GetSaveInfo();
	SaveInfo.ID					 = ID;
	return SaveInfo;
}

void ABaseWorkStation::StartBuild()
{
	BuildingComponent->StartBuild();
}

void ABaseWorkStation::BreakDataLinks_Implementation()
{
	OnLinkBroken.Broadcast();
	OnLinkBroken.RemoveAll(this);
}

FText ABaseWorkStation::DisplayDataLinkText_Implementation()
{
	return FText::FromString("Open " + DisplayName.ToString());
}

void ABaseWorkStation::SetIsBuilt(bool State)
{
	IsBuilt = State;
	if (State == false)
	{
		return;
	}
	OnBuildingReady.ExecuteIfBound(this);
	BuildingComponent->OnBuildingFinisehd.RemoveAll(this);
	BuildingComponent->OnBuildStarted.RemoveAll(this);
	BreakDataLinks_Implementation();
}

void ABaseWorkStation::SetIsConstructing(bool State)
{
	IsConstructing = State;
	OnStartedConstruction.Broadcast(IsConstructing, this);
}


//---------------------CheatSection-----------------------------------
void ABaseWorkStation::ForceBuild()
{
	BuildingComponent->ForceBuild();
}
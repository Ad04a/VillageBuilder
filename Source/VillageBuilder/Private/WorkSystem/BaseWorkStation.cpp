// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkSystem/BaseWorkStation.h"
#include "Components/StorageComponent.h"
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
	BuildingComponent->OnBuildingFinisehd.BindDynamic(this, &ABaseWorkStation::SetIsBuilt);
	BuildingComponent->OnBuildStarted.BindDynamic(this, &ABaseWorkStation::SetIsConstructing);
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
	ProfessionName = StationData->ProfessionName;

}

void ABaseWorkStation::Init(FWorkStationInfoStruct InLoadInfo )
{
	SetActorTransform(InLoadInfo.Transform);
	BuildingComponent->Init(InLoadInfo.BuildingClusterInfo);
	ID = InLoadInfo.ID;
}

FWorkStationInfoStruct ABaseWorkStation::GetSaveInfo()
{
	FWorkStationInfoStruct SaveInfo;
	SaveInfo.Transform		     = GetActorTransform();
	SaveInfo.WorkStationClass    = GetClass();
	SaveInfo.BuildingClusterInfo = BuildingComponent->GetSaveInfo();
	SaveInfo.ID					 = ID;
	return SaveInfo;
}

void ABaseWorkStation::InteractRequest_Implementation(AVillager* InteractingVillager)
{
	if (GetIsBuilt() == false)
	{
		return;
	}
	AVillageMayor* InteractingPlayer = Cast<AVillageMayor>(InteractingVillager);
	if (IsValid(InteractingPlayer) == false)
	{
		return;
	}
	InteractingPlayer->ToggleEmployeeMenu(this);
}

FText ABaseWorkStation::DisplayInteractText_Implementation()
{
	if (GetIsBuilt() == false)
	{
		return FText::FromString(DisplayName.ToString() + " is not ready yet");
	}
	return FText::FromString("Open " + DisplayName.ToString());
}

float ABaseWorkStation::GetModifier(ETrait TraitName) 
{
	if (TraitModifiers.Contains(TraitName) == false)
	{
		return 0;
	}
	return *TraitModifiers.Find(TraitName);
}

void ABaseWorkStation::SetIsBuilt(bool State)
{
	IsBuilt = State;
	if (State == false)
	{
		return;
	}
	OnBuildingReady.ExecuteIfBound(this);
}

void ABaseWorkStation::SetIsConstructing(bool State)
{
	IsConstructing = State;
	if (State == false)
	{
		return;
	}
	OnStartedConstruction.ExecuteIfBound(this);
}

class UBaseBuildingComponent* ABaseWorkStation::GetFirstBuildingComponent()
{
	return BuildingComponent->GetFirstBuildingComponent();
}


//---------------------CheatSection-----------------------------------
void ABaseWorkStation::ForceBuild()
{
	BuildingComponent->ForceBuild();
}
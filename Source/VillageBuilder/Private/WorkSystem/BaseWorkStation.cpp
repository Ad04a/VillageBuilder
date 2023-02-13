// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkSystem/BaseWorkStation.h"
#include "Components/BuildingClusterComponent.h"
#include "Components/StorageComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Items/Item.h"
#include "Characters/VillageMayor.h"

// Sets default values
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

	ToggleStarges(false);
}

void ABaseWorkStation::ReleaseWorker()
{
	HiredVillager = nullptr;
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

TArray<UStorageComponent*> ABaseWorkStation::GetStorages() 
{
	TArray<UStorageComponent*>TempArray;

	TArray<USceneComponent*>ChildrenComponents;
	MeshComponent->GetChildrenComponents(true, ChildrenComponents);
	for (USceneComponent* Child : ChildrenComponents)
	{
		UStorageComponent* StorageComponent = Cast<UStorageComponent>(Child);
		if (IsValid(StorageComponent) == false) {
			continue;
		}
		TempArray.Add(StorageComponent);
	}
	return TempArray;
}

UStorageComponent* ABaseWorkStation::GetRightStorage(TSubclassOf<class AItem> ItemClass)
{
	TArray<UStorageComponent*>Storages = GetStorages();
	for (UStorageComponent* Storage : Storages)
	{
		if (Storage->GetExplicitItemClass() != ItemClass)
		{
			continue;
		}
		return Storage;
	}
	return nullptr;
}

void ABaseWorkStation::ToggleStarges(bool State)
{
	TArray<UStorageComponent*>Storages = GetStorages();
	for (UStorageComponent* Storage : Storages)
	{
		Storage->SetIsActive(State);
	}
}

void ABaseWorkStation::SetIsBuilt(bool State)
{
	IsBuilt = State;
	if (State == false)
	{
		return;
	}
	OnBuildingReady.ExecuteIfBound(this);
	ToggleStarges(State);
}

void ABaseWorkStation::SetIsConstructing(bool State)
{
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

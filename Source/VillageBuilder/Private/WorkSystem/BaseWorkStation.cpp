// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkSystem/BaseWorkStation.h"

// Sets default values
ABaseWorkStation::ABaseWorkStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
	BuildingComponent = CreateDefaultSubobject<UBuildingClusterComponent>(TEXT("BuildingComponent"));
	BuildingComponent->SetupAttachment(MeshComponent);
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
}

void ABaseWorkStation::ReleaseWorker()
{
	HiredVillager = nullptr;
}

void ABaseWorkStation::InteractRequest_Implementation(AVillageMayor* InteractingPlayer)
{
	InteractingPlayer->ToggleEmployeeMenu();
}

FText ABaseWorkStation::DisplayInteractText_Implementation()
{
	return FText::FromString("Open " + DisplayName.ToString());
}




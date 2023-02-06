// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BuilderItem.h"
#include "Characters/Villager.h"
#include "GameModes/GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "WorkSystem/BaseWorkStation.h"

ABuilderItem::ABuilderItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuilderItem::Init(FName StationName)
{
	CurrentStationName = StationName;
	LoadFromDataTable();
	Use(nullptr, EItemActionType::Primary);
}

void ABuilderItem::Use(class AVillager* User, EItemActionType ActionType)
{
	if (CurrentProjection == nullptr)
	{
		SpawnProjection();
		return;
	}

	Super::Use(User, ActionType);
	
}

void ABuilderItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentProjection == nullptr)
	{
		return;
	}
	FVector StartTrace = MeshComponent->GetComponentLocation();
	FVector EndTrace = MeshComponent->GetForwardVector() * Reach + StartTrace;
	FVector NewLocation = FVector(EndTrace.X, EndTrace.Y, 0);
	
	CurrentProjection->SetActorLocation(NewLocation);
}

void ABuilderItem::SetIsActive(bool State)
{
	IsActive = State;
	if (State == true)
	{
		UWorld* World = GetWorld();
		if (IsValid(World) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("ABuilderItem::SetIsActive IsValid(World) == false"));
			return;
		}

		AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
		if (IsValid(GameMode) == false) {
			UE_LOG(LogTemp, Error, TEXT("ABuilderItem::SetIsActive IsValid(GameMode) == false"));
			return;
		}

		AVillageManager* Village = GameMode->GetCurrentVillage(this);
		if (IsValid(Village) == false) {
			UE_LOG(LogTemp, Error, TEXT("ABuilderItem::SetIsActive IsValid(Village) == false"));
			return;
		}

		ABaseWorkStation* WorkStation = Cast<ABaseWorkStation>(SpawnActor());
		if (IsValid(WorkStation) == false) {
			UE_LOG(LogTemp, Error, TEXT("ABuilderItem::SetIsActive IsValid(WorkStation) == false"));
			return;
		}
		Village->AddWorkStationToColony(WorkStation);
		CurrentProjection->Destroy();
	}
	UsingVillager->DropItem();
}

void ABuilderItem::LoadFromDataTable()
{
	if (CurrentStationName == "") {

		Super::LoadFromDataTable();
		return;
	}

	if (IsValid(SecondaryDataTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ABuilderItemLoadFromDataTable() IsValid(DataTable) == false from %s"), *GetClass()->GetName());
		return;
	}

	FBuilderData* BuilderData = SecondaryDataTable->FindRow<FBuilderData>(CurrentStationName, "");

	if (BuilderData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ABuilderItem::LoadFromDataTable() BuilderData == nullptr from %s"), *GetClass()->GetName());
		return;
	}

	ActorToSpawn		 = BuilderData->ActorToSpawn;
	BuildProjectionClass = BuilderData->BuildProjectionClass;
}

void ABuilderItem::SpawnProjection()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ABuilderItem::SpawnProjection() IsValid(World) == false"));
		return ;
	}
	FVector Location = GetSpawnLocation();
	FRotator Rotation = GetSpawnRotation();

	FActorSpawnParameters Params;
	ABuildProjection* SpawnedProjection = World->SpawnActor<ABuildProjection>(BuildProjectionClass, Location, Rotation, Params);
	if (IsValid(SpawnedProjection) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ABuilderItem::SpawnProjection() IsValid(SpawnedActor) == false"));
		return;
	}
	CurrentProjection = SpawnedProjection;
}

void ABuilderItem::OnDrop()
{
	Super::OnDrop();
	Destroy();
}

FVector ABuilderItem::GetSpawnLocation()
{
	if (CurrentProjection == nullptr)
	{
		return FVector(0, 0, 0);
	}

	return CurrentProjection->GetActorLocation();
}

FRotator ABuilderItem::GetSpawnRotation()
{
	if (CurrentProjection == nullptr)
	{
		return FRotator(0, 0, 0);
	}
	return CurrentProjection->GetActorRotation();
}

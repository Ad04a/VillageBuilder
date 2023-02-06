// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BuilderItem.h"
#include "Characters/Villager.h"

void ABuilderItem::Init(FName StationName)
{
	CurrentStationName = StationName;
	LoadFromDataTable();
	
}

void ABuilderItem::Use(class AVillager* User, EItemActionType ActionType)
{
	if (bIsProjecting == false)
	{
		UsingVillager = User;
		
		bIsProjecting = true;
		return;
	}

	Super::Use(User, ActionType);
	
}

void ABuilderItem::Tick(float DeltaTime)
{
	//SpawnProjection
}

void ABuilderItem::SetIsActive(bool State)
{
	IsActive = State;
	if (State == true)
	{
		SpawnActor();
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

	ActorToSpawn = BuilderData->ActorToSpawn;
	
}

void ABuilderItem::OnDrop()
{
	Super::OnDrop();
	Destroy();
}

FVector ABuilderItem::GetSpawnLocation()
{
	return FVector(0, 0, 0);
}

FRotator ABuilderItem::GetSpawnRotation()
{
	return FRotator(0, 0, 0);
}

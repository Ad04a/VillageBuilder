// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SpawningItem.h"
#include "Characters/Villager.h"

void ASpawningItem::Use(class AVillager* User, EItemActionType ActionType)
{
	Super::Use(User, ActionType);
	UsingVillager = User;
}

void ASpawningItem::SetIsActive(bool State)
{
	Super::SetIsActive(State);
	if (State == false)
	{
		return;
	}
	SpawnActor();
	AItem* Copy = UsingVillager->DropItem();
	Destroy();
	Copy->Destroy();
}

AActor* ASpawningItem::SpawnActor()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ASpawningItem::SpawnActor IsValid(World) == false"));
		return nullptr;
	}
	FVector Location = GetSpawnLocation();
	FRotator Rotation = GetSpawnRotation();
	
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* SpawnedActor = World->SpawnActor<AActor>(ActorToSpawn, Location, Rotation, Params);
	if (IsValid(SpawnedActor) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ASpawningItem::SpawnActor IsValid(SpawnedActor) == false"));
		return nullptr; 
	}
	return SpawnedActor;
}

FVector ASpawningItem::GetSpawnLocation()
{
	if (SpawnSocket == "")
	{
		return GetActorLocation();
	}

	return MeshComponent->GetSocketLocation(SpawnSocket);
	
}

FRotator ASpawningItem::GetSpawnRotation()
{
	if (SpawnSocket == "")
	{
		return GetActorRotation();
	}

	return FRotator(0,0,0);
}
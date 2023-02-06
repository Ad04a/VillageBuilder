// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "SpawningItem.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API ASpawningItem : public AItem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditDefaultsOnly)
	FName SpawnSocket;

	virtual void Use(class AVillager* User, EItemActionType ActionType) override;
	virtual AActor* SpawnActor();
	virtual FVector GetSpawnLocation();
	virtual FRotator GetSpawnRotation();
	virtual void SetIsActive(bool State) override;
};

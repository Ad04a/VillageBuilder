// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Headers/Saving/LoadInfo.h"
#include "Headers/Saving/FoliageSaving.h"
#include "Headers/Saving/AnimalSaving.h"
#include "WorkSystem/VillageManager.h"
#include "VillageBuilderPlayerController.h"
#include "VillageBuilderSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UVillageBuilderSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	bool bIsFirstLoad = true;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVillageManagerLoadInfoStruct VillageInfo = FVillageManagerLoadInfoStruct();

	UPROPERTY(VisibleAnywhere, Category = Enviroment)
	TArray<FItemInfoStruct> UnequipedItems;

	UPROPERTY(VisibleAnywhere, Category = Enviroment)
	TArray<FHarvestableFoliageInfoStruct> FoliageInfo;

	UPROPERTY(VisibleAnywhere, Category = Enviroment)
	FAnimalSpawnerInfoStruct GlobalAnimalSpawner = FAnimalSpawnerInfoStruct();

	UPROPERTY(VisibleAnywhere, Category = Player)
	FVillagerLoadInfoStruct PlayerInfo = FVillagerLoadInfoStruct();

	UPROPERTY(VisibleAnywhere, Category = Player)
	FPlayerControllerInfoStruct PlayerControllerInfo = FPlayerControllerInfoStruct();

	UPROPERTY(VisibleAnywhere, Category = Player)
	bool IsPlayerDead = false;

	UPROPERTY(VisibleAnywhere, Category = Player)
	FTransform SpectatorTransform = FTransform();
};

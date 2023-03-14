// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Headers/LoadInfo.h"
#include "Headers/FoliageSaving.h"
#include "Headers/AnimalSaving.h"
#include "WorkSystem/VillageManager.h"
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
	TArray<FItemInfoStruct> UnequipedItems;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVillagerLoadInfoStruct PlayerInfo = FVillagerLoadInfoStruct();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVillageManagerLoadInfoStruct VillageInfo = FVillageManagerLoadInfoStruct();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<FHarvestableFoliageInfoStruct> FoliageInfo;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FAnimalSpawnerInfoStruct GlobalAnimalSpawner = FAnimalSpawnerInfoStruct();
};

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Characters/VillageMayor.h"
#include "Headers/StatAndTraitStructure.h"
#include "GameplayModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API AGameplayModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<AVillager> VillagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<AVillageMayor> PlayerClass;

	UFUNCTION()
	AVillager* SpawnVillager(UWorld* World, bool IsPlayer=false, FVector Position=FVector(0,0,0), FLoadInfoStruct LoadInfo = FLoadInfoStruct());
};

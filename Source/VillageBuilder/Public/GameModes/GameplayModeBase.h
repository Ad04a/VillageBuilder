// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Characters/Villager.h"
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
	TSubclassOf<AVillager> PawnClass;

	UFUNCTION()
	AVillager* SpawnVillager(UWorld* World, bool IsPlayer=false, FVector Position=FVector(0,0,0), FLoadInfoStruct LoadInfo = FLoadInfoStruct());
};

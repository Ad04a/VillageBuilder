// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Characters/VillageMayor.h"
#include "Items/SpawningItem.h"
#include "WorkSystem/VillageManager.h"

#include "Items/BuilderItem.h"

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
	TSubclassOf<AVillageMayor> PlayerClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<ASpawningItem> ColonyFlagClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<ABuilderItem> BuilderItemClass;

	UPROPERTY()
	AVillageManager* Village; //TArray Villages for multicolony feature

public:
	UFUNCTION()
	void SetVillage(AVillageManager* VillageManager); //AddVillage for multicolony feature

	UFUNCTION()
	AVillageManager* GetCurrentVillage(AActor* Entity);
};

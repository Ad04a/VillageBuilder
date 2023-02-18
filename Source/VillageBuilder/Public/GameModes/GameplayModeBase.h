// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Characters/VillageMayor.h"
#include "Items/SpawningItem.h"
#include "WorkSystem/VillageManager.h"

#include "Items/BuilderItem.h"

#include "GameplayModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FErrorSignature);

UCLASS()
class VILLAGEBUILDER_API AGameplayModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	FString SaveSlotName = "";
	class UVillageBuilderSaveGame* LoadedGame;
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

	AVillageMayor* Player;

public:

	FErrorSignature OnErrorLoadingData;

	UFUNCTION()
	void SaveGame(bool bIsAsync = false);

	UFUNCTION()
	void SetVillage(AVillageManager* VillageManager); //AddVillage for multicolony feature

	UFUNCTION()
	AVillageManager* GetCurrentVillage(AActor* Entity);

	UFUNCTION()
	void EndGame();

};

// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Characters/VillageMayor.h"
#include "Items/SpawningItem.h"
#include "WorkSystem/VillageManager.h"

#include "Items/BuilderItem.h"

#include "GameplayModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FErrorHandleSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVisualizeLinkSignature, UDataLink*, Link);

UCLASS()
class VILLAGEBUILDER_API AGameplayModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	FString SaveSlotName = "";
	UPROPERTY()
	class UVillageBuilderSaveGame* LoadedGame;
	FTimerHandle SavenHandle;
protected:
	virtual void StartPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Saving")
	float SaveTime = 1;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<AVillageMayor> PlayerClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<ASpawningItem> ColonyFlagClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<ABuilderItem> BuilderItemClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<AVillageManager> VillageClass;

	UPROPERTY(VisibleAnywhere, Category = "DataLinks")
	TArray<UObject*> CurrentDataLinks;

	UPROPERTY()
	AVillageManager* Village; //TArray Villages for multicolony feature

	AVillageMayor* Player;

	UPROPERTY(EditDefaultsOnly, Category = "Building")
	UDataTable* BuildingDataTable;

	TMap<FString, FName> BuildingsInfo;

	void GetBuildingsInfo();

	UFUNCTION()
	void ReleaseDataLink(class UDataLink* InDataLink);

public:
	FErrorHandleSignature OnErrorLoadingData;
	FErrorHandleSignature OnSaveStarted;
	FErrorHandleSignature OnSaveEnded;
	FErrorHandleSignature OnGameEnd;
	FVisualizeLinkSignature OnLinkNeedsVisualization;

	TArray<FString> GetAllBuildingNames();

	UFUNCTION()
	bool GivePlayerBuildItem(FString StationName);

	UFUNCTION()
	void SaveGame();

	UFUNCTION()
	void SetVillage(AVillageManager* VillageManager); //AddVillage for multicolony feature

	UFUNCTION()
	AVillageManager* GetCurrentVillage(AActor* Entity);

	UFUNCTION()
	void EndGame();

	void LockDataLink(class UDataLink* InDataLink);

	//---------------------CheatSection-----------------------------------
	UFUNCTION(Exec, Category = Cheat)
	void ForceBuildComponents();
};

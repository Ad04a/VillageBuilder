// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameModes/GameplayModeBase.h"
#include "GameModes/VillageBuilderGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "VillageBuilderSaveGame.h"
#include "VillageBuilderPlayerController.h"

void AGameplayModeBase::StartPlay() {

	Super::StartPlay();
	
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(World) == false"));
		return;
	}
	UVillageBuilderGameInstance* GameInstane = Cast<UVillageBuilderGameInstance>(World->GetGameInstance());
	if (IsValid(GameInstane) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AMainMenuModeBase::StartGame() IsValid(GameInstane) == false"));
		OnErrorLoadingData.Broadcast();
		return;
	}
	SaveSlotName = GameInstane->SaveSlotName;
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0) == false)
	{
		OnErrorLoadingData.Broadcast();
		return;
	}
	LoadedGame = Cast<UVillageBuilderSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	FActorSpawnParameters Params;
	Player = World->SpawnActor<AVillageMayor>(PlayerClass, FVector(0,0,0), FRotator(0,0,0), Params);
	Player->Init(LoadedGame->PlayerInfo, SaveSlotName);
	APlayerController* Controller = UGameplayStatics::GetPlayerController(World, 0);
	if (IsValid(Controller) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(Controller) == false"));
	}
	Controller->Possess(Player);
	if (LoadedGame->bIsFirstLoad == true)
	{
		ASpawningItem* VillageManager = World->SpawnActor<ASpawningItem>(ColonyFlagClass, FVector(0, 0, 100), FRotator(0, 0, 0), Params);

		Player->Equip(VillageManager);

		ABuilderItem* BuilderItem = World->SpawnActor<ABuilderItem>(BuilderItemClass, FVector(300, 300, 300), FRotator(0, 0, 0), Params);
		BuilderItem->BindToPlayer("BP_ForesterHut_C", Player);

		ABuilderItem* BuilderItem2 = World->SpawnActor<ABuilderItem>(BuilderItemClass, FVector(500, 500, 300), FRotator(0, 0, 0), Params);
		BuilderItem2->BindToPlayer("BP_BuilderWorkStation_C", Player);

		LoadedGame->bIsFirstLoad = false;
		SaveGame();
		return;
	}
	for (FItemInfoStruct ItemInfo : LoadedGame->UnequipedItems)
	{
		AItem::CreateInstance(this, ItemInfo);
	}
	LoadedGame->UnequipedItems.Empty();

	if (LoadedGame->VillageInfo == FVillageManagerLoadInfoStruct())
	{
		return;
	}
	Village = World->SpawnActor<AVillageManager>(VillageClass, FVector(0, 0, 500), FRotator(0, 0, 0), Params);
	if (IsValid(Village) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(Village) == false"));
	}
	Village->Init(LoadedGame->VillageInfo);
	SaveGame();
}

void AGameplayModeBase::SaveGame()
{
	OnSaveStarted.Broadcast();

	LoadedGame->PlayerInfo  = Player->GetSaveInfo();
	TArray<AActor*> FoundItems;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItem::StaticClass(), FoundItems);
	for (AActor* Actor : FoundItems)
	{
		AItem* Item = Cast<AItem>(Actor);
		if (IsValid(Item) == false)
		{
			continue;
		}
		if (Item->GetSaveAlone() == false)
		{
			continue;
		}
		LoadedGame->UnequipedItems.Add(Item->GetSaveInfo());
	}
	if (IsValid(Village) == true)
	{
		LoadedGame->VillageInfo = Village->GetSaveInfo();
	}

	UGameplayStatics::SaveGameToSlot(LoadedGame, SaveSlotName, 0);
	LoadedGame->UnequipedItems.Empty();
	OnSaveEnded.Broadcast();
}

void AGameplayModeBase::EndGame()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(World) == false"));
		return;
	}
	OnGameEnd.Broadcast();
	SaveGame();
	UGameplayStatics::OpenLevel(World, "MainMenu");
}

void AGameplayModeBase::SetVillage(AVillageManager* VillageManager)
{
	Village = VillageManager;
	OnSaveStarted.AddDynamic(Village, &AVillageManager::PauseTimedSpawn);
	OnSaveEnded.AddDynamic(Village, &AVillageManager::UnPauseTimedSpawn);
	Village->OnStateUpdated.AddDynamic(this, &AGameplayModeBase::SaveGame);
}

AVillageManager* AGameplayModeBase::GetCurrentVillage(AActor* Entity)
{
	//Logic for find in which village the work station is for multicoloni feature
	return Village;
}

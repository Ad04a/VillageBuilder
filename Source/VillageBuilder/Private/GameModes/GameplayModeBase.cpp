// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameModes/GameplayModeBase.h"
#include "GameModes/VillageBuilderGameInstance.h"
#include "VillageBuilderSaveGame.h"
#include "VillageBuilderPlayerController.h"
#include "Components/BaseBuildingComponent.h"
#include "DataTransfers/DataLink.h"

#include "Kismet/GameplayStatics.h"

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
	GetBuildingsInfo();

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

bool AGameplayModeBase::GivePlayerBuildItem(FString StationName)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::GivePlayerBuildItem IsValid(World) == false"));
		return false;
	}
	if (Player->CanEquip() == false)
	{
		return false;
	}
	FActorSpawnParameters Params;
	ABuilderItem* BuilderItem = World->SpawnActor<ABuilderItem>(BuilderItemClass, FVector(0, 0, 300), FRotator(0, 0, 0), Params);
	FName Name = *BuildingsInfo.Find(StationName);
	BuilderItem->BindToPlayer(Name, Player);
	Player->Equip(BuilderItem);
	return true;
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

void AGameplayModeBase::GetBuildingsInfo()
{
	if (IsValid(BuildingDataTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::GetBuildingsInfo IsValid(StationDataTable) == false"));
		return;
	}
	for (FName Row : BuildingDataTable->GetRowNames())
	{

		FWorkStationData* StationData = BuildingDataTable->FindRow<FWorkStationData>(Row, "");

		if (StationData == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::GetBuildingsInfo FWorkStationData == nullptr from %s"), *Row.ToString());
			return;
		}
		UE_LOG(LogTemp, Display, TEXT("AGameplayModeBase::GetBuildingsInfo  %s : %s"), *StationData->DisplayName.ToString() , *Row.ToString());
		BuildingsInfo.Add(StationData->DisplayName.ToString(), Row);
	}
}

TArray<FString> AGameplayModeBase::GetAllBuildingNames()
{
	TArray<FString> Names;
	BuildingsInfo.GenerateKeyArray(Names);
	return Names;
}

void AGameplayModeBase::LockDataLink(UDataLink* InDataLink)
{
	CurrentDataLinks.Add(InDataLink);
	InDataLink->OnLinkBroken.AddDynamic(this, &AGameplayModeBase::ReleaseDataLink);
	if (InDataLink->GetShouldVisualize() == true)
	{
		OnLinkNeedsVisualization.Broadcast(InDataLink);
	}
}

void AGameplayModeBase::ReleaseDataLink(UDataLink* InDataLink)
{
	CurrentDataLinks.Remove(InDataLink);
}

//---------------------CheatSection-----------------------------------

void AGameplayModeBase::ForceBuildComponents()
{
	TArray<AActor*> FoundItems;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseWorkStation::StaticClass(), FoundItems);
	int Sum = 0;
	for (AActor* Actor : FoundItems)
	{
		ABaseWorkStation* Station = Cast<ABaseWorkStation>(Actor);
		if (IsValid(Station) == false)
		{
			continue;
		}
		if (Station->GetIsConstructing() == false)
		{
			continue;
		}
		Sum++;
		Station->ForceBuild();
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Builded " + FString::FromInt(Sum) + " stations");
}
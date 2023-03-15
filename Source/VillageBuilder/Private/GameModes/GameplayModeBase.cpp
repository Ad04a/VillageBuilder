// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameModes/GameplayModeBase.h"
#include "GameModes/VillageBuilderGameInstance.h"
#include "VillageBuilderSaveGame.h"
#include "VillageBuilderPlayerController.h"
#include "Components/BaseBuildingComponent.h"
#include "Components/HarvestableFoliageComponent.h"
#include "DataTransfers/DataLink.h"
#include "Characters/AnimalSpawner.h"
#include "VillageBuilderPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "SignificanceManager.h"
#include "EngineUtils.h"
#include "Runtime/Foliage/Public/InstancedFoliageActor.h"
#include "GameFramework/SpectatorPawn.h"

AGameplayModeBase::AGameplayModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}


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
	LoadBuildingsInfo();

	SaveSlotName = GameInstane->SaveSlotName;
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0) == false)
	{
		OnErrorLoadingData.Broadcast();
		return;
	}
	LoadedGame = Cast<UVillageBuilderSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	AVillageBuilderPlayerController* PlayerController = Cast<AVillageBuilderPlayerController>(UGameplayStatics::GetPlayerController(World, 0));

	if (IsValid(PlayerController) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::SaveGame IsValid(PlayerController) == false"));
		return;
	}
	PlayerController->Init(LoadedGame->PlayerControllerInfo);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	if (LoadedGame->IsPlayerDead == false)
	{
		Player = World->SpawnActor<AVillageMayor>(PlayerClass, FVector(0, 0, 0), FRotator(0, 0, 0), Params);
		Player->Init(LoadedGame->PlayerInfo, SaveSlotName);
		PlayerController->Possess(Player);
		Player->SetProfession("Mayor");
	}
	else
	{
		SpectatorPawn = SpawnSpectator();
		PlayerController->Possess(SpectatorPawn);
		SpectatorPawn->SetActorTransform(LoadedGame->SpectatorTransform);
	}

	if (LoadedGame->bIsFirstLoad == true)
	{
		for (TSubclassOf<AItem > ItemClass : StartingItems)
		{
			Player->PickUp(AItem::SpawnItem(World, ItemClass), true);
		}
		
		LoadedGame->bIsFirstLoad = false;
		SaveGame();
		return;
	}
	for (FItemInfoStruct ItemInfo : LoadedGame->UnequipedItems)
	{
		AItem::CreateInstance(this, ItemInfo);
	}
	LoadedGame->UnequipedItems.Empty();

	for (TActorIterator<AInstancedFoliageActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AInstancedFoliageActor* FoliageMesh = *ActorItr;
		TArray<UActorComponent*> FoliageComponents;
		FoliageMesh->GetComponents(UHarvestableFoliageComponent::StaticClass(), FoliageComponents);
		for (int i = 0; i < FoliageComponents.Num(); i++)
		{
			UHarvestableFoliageComponent* FoliageComponent = Cast<UHarvestableFoliageComponent>(FoliageComponents[i]);
			FoliageComponent->Init(LoadedGame->FoliageInfo[i]);
		}
	}

	TArray<AActor*> Spawners;
	UGameplayStatics::GetAllActorsWithTag(World, SpawnerTag, Spawners);
	if (Spawners.IsEmpty() == true)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::StartPlay No Global Animal Spawner Found"));
		return;
	}
	AAnimalSpawner* AnimalSpawner = Cast<AAnimalSpawner>(Spawners[0]);
	if (IsValid(AnimalSpawner) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::StartPlay IsValid(AnimalSpawner) == false"));
		return;
	}

	AnimalSpawner->Init(LoadedGame->GlobalAnimalSpawner);

	if (LoadedGame->VillageInfo == FVillageManagerLoadInfoStruct())
	{
		SaveGame();
		return;
	}
	Village = World->SpawnActor<AVillageManager>(VillageClass, FVector(0, 0, 500), FRotator(0, 0, 0), Params);
	if (IsValid(Village) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(Village) == false"));
	}
	Village->Init(LoadedGame->VillageInfo);
	SaveGame();
}

void AGameplayModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::Tick IsValid(World) == false"));
		return;
	}
	USignificanceManager* SignificanceManager = FSignificanceManagerModule::Get(World);
	if (IsValid(SignificanceManager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::Tick IsValid(SignificanceManager) == false"));
		return;
	}
	TArray<FTransform> PlayerViepoints;
	FVector Location;
	FRotator Rotation;
	for (int i = 0; i < UGameplayStatics::GetNumPlayerControllers(World); i++)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, i);
		PlayerController->GetPlayerViewPoint(Location, Rotation);
		PlayerViepoints.Emplace(Rotation, Location, FVector::OneVector);
	}
	SignificanceManager->Update(PlayerViepoints);

}

void AGameplayModeBase::SaveGame()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::SaveGame IsValid(World) == false"));
		return;
	}

	OnSaveStarted.Broadcast();

	AVillageBuilderPlayerController* PlayerController = Cast<AVillageBuilderPlayerController>(UGameplayStatics::GetPlayerController(World, 0));

	if (IsValid(PlayerController) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::SaveGame IsValid(PlayerController) == false"));
		return;
	}
	LoadedGame->PlayerControllerInfo = PlayerController->GetSaveInfo();
	if (PlayerController->IsPlayerValid() == true)
	{
		LoadedGame->PlayerInfo = Player->GetSaveInfo();
		LoadedGame->IsPlayerDead = false;
	}
	else
	{ 
		LoadedGame->SpectatorTransform = SpawnSpectator()->GetActorTransform();
		LoadedGame->IsPlayerDead = true;
	}

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

	LoadedGame->FoliageInfo.Empty();

	for (TActorIterator<AInstancedFoliageActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AInstancedFoliageActor* FoliageMesh = *ActorItr;
		TArray<UActorComponent*> FoliageComponents;
		FoliageMesh->GetComponents(UHarvestableFoliageComponent::StaticClass(), FoliageComponents);
		for (int i = 0; i < FoliageComponents.Num(); i++)
		{
			UHarvestableFoliageComponent* FoliageComponent = Cast<UHarvestableFoliageComponent>(FoliageComponents[i]);
			LoadedGame->FoliageInfo.Add(FoliageComponent->GetSaveInfo());
		}
		
	}
	TArray<AActor*> Spawners;
	UGameplayStatics::GetAllActorsWithTag(World, SpawnerTag, Spawners);
	if (Spawners.IsEmpty() == true)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::SaveGame No Global Animal Spawner Found"));
		return;
	}
	AAnimalSpawner* AnimalSpawner = Cast<AAnimalSpawner>(Spawners[0]);
	if (IsValid(AnimalSpawner) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::SaveGame IsValid(AnimalSpawner) == false"));
		return;
	}
	LoadedGame->GlobalAnimalSpawner = AnimalSpawner->GetSaveInfo();

	UGameplayStatics::SaveGameToSlot(LoadedGame, SaveSlotName, 0);
	LoadedGame->UnequipedItems.Empty();
	OnSaveEnded.Broadcast();
}


void AGameplayModeBase::DeleteSave()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::DeleteSave IsValid(World) == false"));
		return;
	}
	OnGameEnd.Broadcast();
	UGameplayStatics::DeleteGameInSlot(SaveSlotName, 0);
	UGameplayStatics::OpenLevel(World, MainMenu);
}

void AGameplayModeBase::OnPlayerDeath( AVillager* InPlayer)
{
	SpectatorPawn = SpawnSpectator();
	PlayerControllers[0]->Possess(SpectatorPawn);
	SpectatorPawn->SetActorTransform(InPlayer->GetActorTransform());
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
	UGameplayStatics::OpenLevel(World, MainMenu);
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

void AGameplayModeBase::LoadBuildingsInfo()
{
	if (IsValid(BuildingDataTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::LoadBuildingsInfo IsValid(StationDataTable) == false"));
		return;
	}
	for (FName Row : BuildingDataTable->GetRowNames())
	{

		FWorkStationData* StationData = BuildingDataTable->FindRow<FWorkStationData>(Row, "");

		if (StationData == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::LoadBuildingsInfo FWorkStationData == nullptr from %s"), *Row.ToString());
			return;
		}
		UE_LOG(LogTemp, Display, TEXT("AGameplayModeBase::LoadBuildingsInfo  %s : %s"), *StationData->DisplayName.ToString() , *Row.ToString());
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

ASpectatorPawn* AGameplayModeBase::SpawnSpectator()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::SpawnSpectator IsValid(World) == false"));
		return nullptr;
	}
	FVector Location = FVector(0,0,0);
	FRotator Rotation = FRotator(0, 0, 0);
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ASpectatorPawn* Spectator = World->SpawnActor<ASpectatorPawn>(SpectatorClass, Location, Rotation, Params);
	if (IsValid(Spectator) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayModeBase::SpawnSpectator IsValid(World) == false"));
		return nullptr;
	}
	return Spectator;
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

void AGameplayModeBase::SpawnVillager(int Count)
{
	for (int i = 0; i < Count; i++)
	{
		Village->SpawnVillager(FVector(0, 0, 200 * i));
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Spawned " + FString::FromInt(Count) + " villagers");
}


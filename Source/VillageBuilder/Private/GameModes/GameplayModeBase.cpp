// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameModes/GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "VillageBuilderPlayerController.h"

void AGameplayModeBase::StartPlay() {

	Super::StartPlay();
	
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(World) == false"));
		return;
	}
	FActorSpawnParameters Params;
	AVillageMayor* Player = World->SpawnActor<AVillageMayor>(PlayerClass, FVector(0,0,0), FRotator(0,0,0), Params);
	Player->Init();
	APlayerController* Controller = UGameplayStatics::GetPlayerController(World, 0);
	if (IsValid(Controller) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(Controller) == false"));
	}
	Controller->Possess(Player);

	ASpawningItem* VillageManager = World->SpawnActor<ASpawningItem>(ColonyFlagClass, FVector(0, 0, 100), FRotator(0, 0, 0), Params);

	Player->Equip(VillageManager);

	ABuilderItem* BuilderItem = World->SpawnActor<ABuilderItem>(BuilderItemClass, FVector(300, 300, 300), FRotator(0, 0, 0), Params);
	BuilderItem->Init("BP_BuilderWorkStation_C", Player);
}

void AGameplayModeBase::SetVillage(AVillageManager* VillageManager)
{
	Village = VillageManager;
}

AVillageManager* AGameplayModeBase::GetCurrentVillage(AActor* Entity)
{
	//Logic for find in which village the work station is for multicoloni feature
	return Village;
}

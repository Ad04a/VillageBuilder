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
	AVillager* Player = World->SpawnActor<AVillager>(PlayerClass, FVector(0,0,0), FRotator(0,0,0), Params);
	Player->Init();
	APlayerController* Controller = UGameplayStatics::GetPlayerController(World, 0);
	if (IsValid(Controller) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(Controller) == false"));
	}
	Controller->Possess(Player);

	AVillageManager* VillageManager = World->SpawnActor<AVillageManager>(VillageManagerClass, FVector(0, 0, 100), FRotator(0, 0, 0), Params);

	Player->Equip(VillageManager);
}



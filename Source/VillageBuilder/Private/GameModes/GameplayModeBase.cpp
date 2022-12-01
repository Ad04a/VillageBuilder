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
	

	AVillager* Player = World->SpawnActor<AVillager>(PawnClass, FVector(0, 0, 0), FRotator());
	
	if (IsValid(Player) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(Player) == false"));
		return;
	}
	Player->Init();



	AVillager* Companion1 = World->SpawnActor<AVillager>(PawnClass, FVector(100, 100, 0), FRotator());
	if (IsValid(Companion1) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(Companion1) == false"));
		return;
	}
	AVillager* Companion2 = World->SpawnActor<AVillager>(PawnClass, FVector(50, 50, 0), FRotator());
	if (IsValid(Companion2) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(Companion2) == false"));
		return;
	}
	Companion1->Init();
	Companion2->Init();



	APlayerController* Controller = UGameplayStatics::GetPlayerController(World, 0);
	if (IsValid(Controller) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(Controller) == false"));
	}
	Controller->Possess(Player);
}
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
	

	AVillager* Player = SpawnVillager(World, true);
	AVillager* Companion1 = SpawnVillager(World, false, FVector(100, 100, 0));
	AVillager* Companion2 = SpawnVillager(World, false, FVector(200, 200, 0));

	APlayerController* Controller = UGameplayStatics::GetPlayerController(World, 0);
	if (IsValid(Controller) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::StartPlay IsValid(Controller) == false"));
	}
	Controller->Possess(Player);
}

AVillager* AGameplayModeBase::SpawnVillager(UWorld* World, bool IsPlayer, FVector Position, FLoadInfoStruct LoadInfo)
{
	FVector Location = Position;
	FRotator Rotation = FRotator(0, 0, 0);
	FActorSpawnParameters Params;
	TSubclassOf<AVillager> ClassToSpawn = VillagerClass;
	if (IsPlayer)
	{
		Params.Name = FName("Player");
		ClassToSpawn = PlayerClass;
	}

	if(LoadInfo != FLoadInfoStruct())
	{
		Location = LoadInfo.Transform.GetLocation();
		Rotation = LoadInfo.Transform.Rotator();
	}
		
	AVillager* Villager = World->SpawnActor<AVillager>(ClassToSpawn, Location, Rotation, Params);

	if (IsValid(Villager) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderGameModeBase::SpawnVillager IsValid(Player) == false"));
		return nullptr;
	}

	Villager->Init(LoadInfo);

	return Villager;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Headers/AIStates.h"
#include "Headers/AnimalSaving.h"
#include "AnimalSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpawnSignature);

UCLASS()
class VILLAGEBUILDER_API AAnimalSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimalSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Bounds)
	float SpawnRadius = 0;

	UPROPERTY(EditAnywhere, Category = Bounds)
	float DisableRadius = 0;

	UPROPERTY(EditAnywhere, Category = Bounds)
	float EnableRadius = 0;

	UPROPERTY(EditAnywhere, Category = Spawning)
	float SpawnTime = 10;

	UPROPERTY(VisibleAnywhere, Category = Spawning)
	float CurrentSpawnTime = 0;

	UPROPERTY(EditAnywhere, Category = Spawning)
	int MaxAnimals = 15;

	UPROPERTY(EditAnywhere, Category = Spawning)
	TArray<TSubclassOf<class AAnimal>> AnimalTypes;

	UPROPERTY(VisibleAnywhere, Category = Spawning)
	TArray<class AAnimal*> ActiveAnimals;

	UPROPERTY(VisibleAnywhere, Category = Spawning)
	TArray<class AAnimal*> DisabledAnimals;

	UPROPERTY(EditAnywhere, Category = Grid)
	float StartX = 0;

	UPROPERTY(EditAnywhere, Category = Grid)
	float EndX = 0;

	UPROPERTY(EditAnywhere, Category = Grid)
	float StartY = 0;

	UPROPERTY(EditAnywhere, Category = Grid)
	float EndY = 0;

	UPROPERTY(EditAnywhere, Category = Animals)
	float LifeTime = 2;

	UPROPERTY(EditAnywhere, Category = Animals)
	float DisableDistance = 4000;

	class AAnimal* SpawnAnimal(FVector OriginLocation);

	UFUNCTION()
	void RegisterAnimalState(class APawn* ControlledPawn, EAIState State);

	UFUNCTION()
	void RegisterSpawnRequest(FVector OriginLocation);

	FSpawnSignature OnSpawnEmited;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Init(FAnimalSpawnerInfoStruct InLoadInfo);
	FAnimalSpawnerInfoStruct GetSaveInfo();
};

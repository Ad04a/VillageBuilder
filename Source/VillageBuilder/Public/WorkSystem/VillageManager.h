// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Headers/StatAndTraitStructure.h"
#include "Characters/Villager.h"
#include "VillageManager.generated.h"

UCLASS()
class VILLAGEBUILDER_API AVillageManager : public AItem 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVillageManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<AVillager*> Villagers;

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<AVillager> VillagerClass;

	UFUNCTION()
	AVillager* SpawnVillager(FVector Position = FVector(0, 0, 0), FLoadInfoStruct LoadInfo = FLoadInfoStruct());

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

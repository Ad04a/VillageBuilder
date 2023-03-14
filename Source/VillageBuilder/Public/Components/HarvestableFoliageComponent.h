// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoliageInstancedStaticMeshComponent.h"
#include "Enviroment/HarvestableActor.h"
#include "Headers/FoliageSaving.h"
#include "HarvestableFoliageComponent.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UHarvestableFoliageComponent : public UFoliageInstancedStaticMeshComponent
{
	GENERATED_BODY()


public:
	UHarvestableFoliageComponent();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(int32 InstanceIndex, float Damage, class AController* InstigatedBy, FVector HitLocation, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);
	
	UPROPERTY(EditDefaultsOnly)
	float InstanceBaseHealth = 100;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHarvestableActor> HarvestableActorClass;

	TArray<float> PerInstanceHealth;

	TArray<int> RemovedIndexes;

public:
	void Init(FHarvestableFoliageInfoStruct InLoadInfo);

	FHarvestableFoliageInfoStruct GetSaveInfo();
};

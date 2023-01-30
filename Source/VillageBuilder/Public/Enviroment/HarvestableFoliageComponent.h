// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoliageInstancedStaticMeshComponent.h"
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

	UFUNCTION()
	void TakeDamage(int32 InstanceIndex, float Damage, class AController* InstigatedBy, FVector HitLocation, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);
	
};

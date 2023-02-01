// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ItemCarrierComponent.h"
#include "HarvestableActor.generated.h"

UCLASS(BlueprintType)
class VILLAGEBUILDER_API AHarvestableActor : public AActor
{
	GENERATED_BODY()

public:

	AHarvestableActor();

	UPROPERTY(EditDefaultsOnly, Category = Harvestable)
	UItemCarrierComponent* ItemCarrierComponent;

	UFUNCTION()
	void Disappear();


};

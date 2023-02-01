// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enviroment/HarvestableActor.h"
#include "HarvestableRock.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API AHarvestableRock : public AHarvestableActor
{
	GENERATED_BODY()

public:
	AHarvestableRock();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent = nullptr;

	virtual void BeginPlay() override;
};

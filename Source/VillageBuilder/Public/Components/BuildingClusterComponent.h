// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "BuildingClusterComponent.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBuildingClusterComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* MainMaterial;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Items/Item.h"
#include "BaseBuildingComponent.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBaseBuildingComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UBaseBuildingComponent();

private:
	bool bIsPlaced = false;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AItem> NeededItem;

	UFUNCTION()
	void Touched(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};

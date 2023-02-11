// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Items/Item.h"
#include "BaseBuildingComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FComponentStateSignature, bool, State);

UCLASS()
class VILLAGEBUILDER_API UBaseBuildingComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UBaseBuildingComponent();

private:
	bool bIsPlaced = false;
	bool bIsActive = false;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AItem> NeededItem;

	UFUNCTION()
	void Touched(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	FComponentStateSignature OnComponentStateChange;
	void SetIsActive(bool State);
};

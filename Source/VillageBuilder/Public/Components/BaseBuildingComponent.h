// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Items/Item.h"
#include "Headers/Interactable.h"
#include "BaseBuildingComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FComponentStateSignature, bool, State);

UCLASS()
class VILLAGEBUILDER_API UBaseBuildingComponent : public UStaticMeshComponent, public IInteractable
{
	GENERATED_BODY()

public:
	UBaseBuildingComponent();

private:
	bool bIsPlaced = false;
	bool bIsActive = false;

	void Build();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AItem> NeededItem;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* PlacedMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Interact")
	FText InteractionText;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractRequest(class AVillager* InteractingVillager);
	virtual void InteractRequest_Implementation(class AVillager* InteractingVillager);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FText DisplayInteractText();
	virtual FText DisplayInteractText_Implementation();

public:
	FComponentStateSignature OnComponentStateChange;
	void SetIsActive(bool State);
	TSubclassOf<AItem> GetNeededClass(){return NeededItem;}
};

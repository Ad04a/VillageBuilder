// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Headers/Interactable.h"
#include "BuildingClusterComponent.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBuildingClusterComponent : public UStaticMeshComponent, public IInteractable
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* MainMaterial;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractRequest(class AVillager* InteractingVillager);
	virtual void InteractRequest_Implementation(class AVillager* InteractingVillager);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FText DisplayInteractText();
	virtual FText DisplayInteractText_Implementation();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ItemCarrierComponent.h"
#include "Headers/Interactable.h"
#include "StorageComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VILLAGEBUILDER_API UStorageComponent : public UItemCarrierComponent, public IInteractable
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly, Category = Content)
	int MaxNumberOfItems;

	UPROPERTY(EditDefaultsOnly, Category = Content)
	TSubclassOf<AItem> ExplicitItemClass;

	UPROPERTY(EditDefaultsOnly, Category = Content)
	TArray<FTransform> ItemTransforms;

	UPROPERTY(EditDefaultsOnly, Category = "Interact")
	FText InteractionText;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractRequest(class AVillager* InteractingVillager);
	virtual void InteractRequest_Implementation(class AVillager* InteractingVillager);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FText DisplayInteractText();
	virtual FText DisplayInteractText_Implementation();

	bool PlaceItem(AItem* InItem);

	TSubclassOf<AItem> GetItemClass();
public:
	TSubclassOf<AItem> GetExplicitItemClass()const {return ExplicitItemClass;}
	bool GetIsFull();

};

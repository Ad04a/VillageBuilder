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
	FText InteractionText;

	UPROPERTY(EditDefaultsOnly, Category = Content)
	int MaxNumberOfItems;

	UPROPERTY(EditDefaultsOnly, Category = Content)
	TEnumAsByte<EItemType> ExplicitItemType;

	UPROPERTY(EditDefaultsOnly, Category = Content)
	TArray<FTransform> ItemTransforms;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractRequest(class AVillageMayor* InteractingPlayer);
	virtual void InteractRequest_Implementation(class AVillageMayor* InteractingPlayer);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FText DisplayInteractText();
	virtual FText DisplayInteractText_Implementation();

	bool PlaceItem(AItem* InItem);

	TSubclassOf<AItem> GetItemClass();
public:
	TEnumAsByte<EItemType> GetExplicitItemType()const {return ExplicitItemType;}

};

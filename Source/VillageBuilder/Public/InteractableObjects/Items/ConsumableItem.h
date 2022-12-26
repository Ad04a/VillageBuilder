// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObjects/Items/Item.h"
#include "Headers/StatAndTraitEnums.h"
#include "ConsumableItem.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FConsumableItemInfoStruct : public FItemInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	int NumberOfUses = 0;

};

UCLASS()
class VILLAGEBUILDER_API AConsumableItem : public AItem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	float ConsumeValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	TEnumAsByte<EStat> StatToUpdate;
	
public:
	virtual void Use(class AVillager* User) override;

	//virtual FItemInfoStruct GetItemInfo() override;
};


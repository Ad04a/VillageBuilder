// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "ConsumableItem.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API AConsumableItem : public AItem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	float ConsumeValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	TEnumAsByte<EStat> StatToUpdate;

	
	virtual void Use(class AVillager* User) override;
};


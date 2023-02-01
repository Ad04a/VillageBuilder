// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Headers/StatAndTraitEnums.h"
#include "ConsumableItem.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FConsumableItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ConsumeValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EStat> StatToUpdate;
};

UCLASS()
class VILLAGEBUILDER_API AConsumableItem : public AItem
{
	GENERATED_BODY()

public:
	AConsumableItem();

protected:

	virtual void BeginPlay() override;

	virtual void LoadFromDataTable() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	float ConsumeValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	TEnumAsByte<EStat> StatToUpdate;
	
public:
	virtual void Use(class AVillager* User, EItemActionType ActionType) override;

	//virtual FItemInfoStruct GetItemInfo() override;
};


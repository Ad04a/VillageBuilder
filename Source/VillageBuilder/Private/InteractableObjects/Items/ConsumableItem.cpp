// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Items/ConsumableItem.h"
#include "Characters/Villager.h"

void AConsumableItem::Use(AVillager* User)
{
	User->AddStatValue(StatToUpdate, ConsumeValue);
	Destroy();
}

	/*s
FItemInfoStruct AConsumableItem::GetItemInfo()
{
	FConsumableItemInfoStruct ItemInfo;
	ItemInfo.ItemClass = GetClass();
	ItemInfo.NumberOfUses = 5;
	UE_LOG(LogTemp, Error, TEXT("AConsumableItem::GetItemInfo %d"), ItemInfo.NumberOfUses);
	return ItemInfo;
}*/


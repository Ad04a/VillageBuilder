// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ConsumableItem.h"

void AConsumableItem::Use(AVillager* User)
{
	User->AddStatValue(StatToUpdate, ConsumeValue);
}

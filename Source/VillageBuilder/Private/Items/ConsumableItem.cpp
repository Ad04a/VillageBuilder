// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ConsumableItem.h"
#include "Characters/Villager.h"

AConsumableItem::AConsumableItem()
{
	
}

void AConsumableItem::BeginPlay()
{
	Super::BeginPlay();
	LoadFromDataTable();
}

void AConsumableItem::Use(AVillager* User, EItemActionType ActionType)
{
	Super::Use(User, ActionType);
	if (ActionType == EItemActionType::Secondary)
	{
		User->DropItem();
		return;
	}
	User->AddStatValue(StatToUpdate, ConsumeValue);
	Destroy();
}

void AConsumableItem::LoadFromDataTable()
{
	Super::LoadFromDataTable();

	if (IsValid(SecondaryDataTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AConsumableItem::LoadFromDataTable() IsValid(DataTable) == false from %s"), *GetClass()->GetName());
		return;
	}

	FConsumableItemData* ConsumableItemData = SecondaryDataTable->FindRow<FConsumableItemData>(GetClass()->GetFName(), "");

	if (ConsumableItemData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AConsumableItem::LoadFromDataTable() ConsumableItemData == nullptr from %s"), *GetClass()->GetName());
		return;
	}

	ConsumeValue = ConsumableItemData->ConsumeValue;
	StatToUpdate = ConsumableItemData->StatToUpdate;
}


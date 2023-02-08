// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StorageComponent.h"
#include "Characters/VillageMayor.h"


void UStorageComponent::InteractRequest_Implementation(class AVillageMayor* InteractingPlayer)
{
	if (InteractingPlayer->GetEquipItemType() == EItemType::Default)
	{
		AItem* TempItem = DropItem(GetItemClass());
		InteractingPlayer->Equip(TempItem);
		return;
	}
	if (InteractingPlayer->GetEquipItemType()!= ExplicitItemType)
	{
		return;
	}
	AItem* TempItem = InteractingPlayer->GetItem();
	if (PlaceItem(TempItem) == false)
	{
		return;
	}
	InteractingPlayer->DropItem();
	TempItem->Destroy();
}

bool UStorageComponent::PlaceItem(AItem* InItem)
{
	if (IsValid(InItem) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UStorageComponent::PlaceItem IsValid(InItem) == false"));
		return false;
	}
	TArray<int> NumItems;
	Content.GenerateValueArray(NumItems);
	int CurrentItems = 0;
	for (int i = 0; i < NumItems.Num(); i++)
	{
		CurrentItems += NumItems[i];
	}
	if (CurrentItems >= MaxNumberOfItems)
	{
		return false;
	}
	Super::AddItem(InItem);
	return true;
}

TSubclassOf<AItem> UStorageComponent::GetItemClass()
{
	TArray<TSubclassOf<AItem>> TempArray = Super::GetItemTypes();
	if (TempArray.Num() < 1)
	{
		return AItem::StaticClass();
	}
	return TempArray[0];
}

FText UStorageComponent::DisplayInteractText_Implementation()
{
	return InteractionText;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StorageComponent.h"
#include "Characters/VillageMayor.h"

void UStorageComponent::Init(FStorageInfoStruct InLoadInfo )
{
	if (InLoadInfo != FStorageInfoStruct()) 
	{
		Items = InLoadInfo.Items;
		LockedSlots = InLoadInfo.LockedSlots;
		ItemRows = InLoadInfo.ItemRows;
		return;
	}
	if (IsValid(StorageDataTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UStorageComponent::Init IsValid(StorageDataTable) == false from %s"), *GetClass()->GetName());
		return;
	}

	FStorageData* StorageData = StorageDataTable->FindRow<FStorageData>(RollToRead, "");

	if (StorageData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UStorageComponent::Init StorageData == nullptr from %s"), *GetClass()->GetName());
		return;
	}

	ItemRows = StorageData->ItemRows;
}

FStorageInfoStruct UStorageComponent::GetSaveInfo()
{
	FStorageInfoStruct SaveInfo;
	SaveInfo.Items		 = Items;
	SaveInfo.LockedSlots = LockedSlots;
	SaveInfo.ItemRows    = ItemRows;

	return SaveInfo;
}

TPair<int, int>  UStorageComponent::CanPlace(AItem* ItemToPlace, TPair<int, int> DesiredPosition)
{
	int TargetSlots = ItemToPlace->GetSlots();
	if (DesiredPosition != TPair<int, int>())
	{
		return TPair<int, int>(-1,-1);
	}
	for (FStorageRow Row : ItemRows)
	{
		int Unocupied = 0;
		for (int i = 0; i<Row.ItemSlots.Num(); i++)
		{	
			if (Row.ItemSlots[i] == -1)
			{
				Unocupied++;
			}
			else
			{
				Unocupied = 0;
			}
			UE_LOG(LogTemp, Display, TEXT("i: %d, Row.ItemSlots[i]: %d, Unocupied: %d"), i, Row.ItemSlots[i], Unocupied);
			if (Unocupied == TargetSlots)
			{
				return TPair<int, int>(ItemRows.IndexOfByKey(Row), i-Unocupied+1);
			}

		}
	}
	return TPair<int, int>(-1,-1);
}

bool UStorageComponent::PlaceItem(AItem* InItem)
{
	TPair<int, int> Start = CanPlace(InItem);
	int StartRow = 0;
	if (Start == TPair<int, int>(-1,-1))
	{
		UE_LOG(LogTemp, Display, TEXT("No Valid Position to equip %s in %s"), *InItem->GetClass()->GetName(),*GetClass()->GetName());
		return false;
	}
	FItemInfoStruct ItemInfo = InItem->GetSaveInfo();
	Items.Add(ItemInfo);
	for (int i = 0; i < InItem->GetSlots(); i++)
	{
		ItemRows[Start.Key].ItemSlots[Start.Value+i] = Items.IndexOfByKey(ItemInfo);
	}
	InItem->Destroy();
	return true;
}


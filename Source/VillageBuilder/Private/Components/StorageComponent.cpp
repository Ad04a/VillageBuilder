// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StorageComponent.h"
#include "Characters/VillageMayor.h"

void UStorageComponent::Init(FStorageInfoStruct InLoadInfo )
{
	if (InLoadInfo == FStorageInfoStruct()) 
	{
		return;
	}
	Items       = InLoadInfo.Items;
	LockedSlots = InLoadInfo.LockedSlots;
	ItemRows    = InLoadInfo.ItemRows;
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
		return TPair<int, int>();
	}
	int Start = 0;
	int Counter = Start;
	for (FStorageRow Row : ItemRows)
	{
		int Unocupied = 0;
		for (int Slot : Row.ItemSlots)
		{
			if (Slot == -1)
			{
				Start = Counter;
				Unocupied ++;
			}
			if (Unocupied == TargetSlots)
			{
				
				return TPair<int, int>(ItemRows.IndexOfByKey(Row), Start);
			}

			Counter++;
		}
	}
	return TPair<int, int>();
}

bool UStorageComponent::PlaceItem(AItem* InItem)
{
	TPair<int, int> Start = CanPlace(InItem);
	int StartRow = 0;
	if (Start == TPair<int, int>())
	{
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


// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StorageComponent.h"
#include "Items/StoredItemInfo.h"
#include "Items/Item.h"

void UStorageComponent::Init(FStorageInfoStruct InLoadInfo )
{
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

	Rows	 = StorageData->Rows;
	Columns  = StorageData->Columns;
	Items.Init(nullptr, Rows * Columns);
	if (false)
	{
		Items.Init(nullptr, Rows * Columns);
		return;
	}
	Items.Init(nullptr, Rows * Columns);
}


FStorageInfoStruct UStorageComponent::GetSaveInfo()
{
	FStorageInfoStruct SaveInfo;
	//SaveInfo.Items		 = Items;

	return SaveInfo;
}

TPair<bool, UStoredItemInfo*> UStorageComponent::TryGetItem(int ItemIndex)
{
	TPair<bool, UStoredItemInfo*> Result;
	Result.Key = Items.IsValidIndex(ItemIndex);
	if (Result.Key == false)
	{
		return Result;
	}
	Result.Value = Items[ItemIndex];
	return Result;
}

FIntPoint UStorageComponent::GetTileByIndex(int Index)
{
	FIntPoint Tile;
	Tile.X = Index % Columns;
	Tile.Y = Index / Columns;
	return Tile;
}

int UStorageComponent::GetIndexByTile(FIntPoint InTile)
{
	return Columns * InTile.Y + InTile.X;
}

bool UStorageComponent::IsPositionValid(FIntPoint Position)
{
	return Position.X > -1 && Position.X < Columns&& Position.Y > -1 && Position.Y < Rows;
}

TArray<FIntPoint> UStorageComponent::GetAllTiles(FIntPoint ItemSlots, int DesiredPosition)
{
	TArray<FIntPoint> Tiles;
	FIntPoint TargetPosition = GetTileByIndex(DesiredPosition);
	FIntPoint Tile;
	for (int X = TargetPosition.X; X < (TargetPosition.X + ItemSlots.X); X++)
	{
		for (int Y = TargetPosition.Y; Y < (TargetPosition.Y + ItemSlots.Y); Y++)
		{
			Tile.X = X;
			Tile.Y = Y;
			Tiles.Add(Tile);
		}
	}
	return Tiles;
}

bool  UStorageComponent::CanPlace(FIntPoint ItemSlots, int DesiredPosition)
{
	
	TArray<FIntPoint> Tiles = GetAllTiles(ItemSlots, DesiredPosition);
	for (FIntPoint Tile : Tiles)
	{
		if (IsPositionValid(Tile) == false)
		{
			return false;
		}
		TPair<bool, UStoredItemInfo* > TileState = TryGetItem(GetIndexByTile(Tile));
		if (TileState.Key == false)
		{
			return false;
		}
		if (IsValid(TileState.Value) == true)
		{
			return false;
		}
	}
	
	return true;
}

bool UStorageComponent::TryPlaceItem(UStoredItemInfo* InItemInfo)
{
	if (IsValid(InItemInfo) == false)
	{
		return false;
	}
	for (int i = 0; i < Items.Num(); i++)
	{
		if (CanPlace(InItemInfo->GetSlots(), i) == false)
		{
			continue;
		}
		AddItemAt(InItemInfo, i);
		return true;
	}
	return false;
}

bool UStorageComponent::TryPlaceItemAtIndex(UStoredItemInfo* InItemInfo, int Index)
{
	if (IsValid(InItemInfo) == false)
	{
		return false;
	}
	if (Items.IsValidIndex(Index)==false)
	{
		UE_LOG(LogTemp, Display, TEXT("UStorageComponent::TryPlaceItemAtIndex Items.IsValidIndex(Index = %d)==false"), Index);
		return false;
	}
	if (CanPlace(InItemInfo->GetSlots(), Index) == false)
	{
		return false;
	}
	AddItemAt(InItemInfo, Index);
	return true;
}

void UStorageComponent::AddItemAt(UStoredItemInfo* InItemInfo, int PlaceIndex)
{
	TArray<FIntPoint> Tiles = GetAllTiles(InItemInfo->GetSlots(), PlaceIndex);
	for (FIntPoint Tile : Tiles)
	{
		Items[GetIndexByTile(Tile)] = InItemInfo;
	}
	SendUpdatedItems();
}


TMap<UStoredItemInfo*, FIntPoint> UStorageComponent::GetAllItems()
{
	TMap<UStoredItemInfo*, FIntPoint> AllItems;
	for (UStoredItemInfo* Item : Items)
	{
		if (IsValid(Item) == false)
		{
			continue;
		}
		if (AllItems.Contains(Item) == true)
		{
			continue;
		}
		AllItems.Add(Item, GetTileByIndex(Items.IndexOfByKey(Item)));
	}
	return AllItems;
}

UStoredItemInfo* UStorageComponent::TakeItemByNumeration(int Numeration)
{
	TMap<UStoredItemInfo*, FIntPoint> ItemData = GetAllItems();
	TArray<UStoredItemInfo*> SearchItems;
	ItemData.GenerateKeyArray(SearchItems);
	if (SearchItems.IsValidIndex(Numeration) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UStorageComponent::TakeItemByNumeration SearchItems.IsValidIndex(Numeration = %d) == false"), Numeration);
		return nullptr;
	}
	UStoredItemInfo* Item = SearchItems[Numeration];
	RemoveItem(Item);

	return Item;
}

void UStorageComponent::RemoveItem(UStoredItemInfo* ItemToRemove)
{
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i] == ItemToRemove)
		{
			Items[i] = nullptr;
		}
	}
	SendUpdatedItems();
	ItemToRemove->ConditionalBeginDestroy();
}

void UStorageComponent::DropItem(UStoredItemInfo* InItemInfo)
{
	if (IsValid(InItemInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UStorageComponent::DropItem IsValid(InItemInfo) == false"));
		return;
	}
	AItem* Item = AItem::CreateInstance(this, InItemInfo->GetItemInfo());
	RemoveItem(InItemInfo);
	Item->SetEnablePhysics(true);
	Item->OnDrop();
	Item->SetActorLocation(GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector()*150);
}

void UStorageComponent::DropFirst()
{
	DropItem(Items[0]);
}

void UStorageComponent::PlaceItem(AItem* ItemToAdd, FIntPoint Coordinates)
{
	if (IsValid(ItemToAdd) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UStorageComponent::PlaceItem IsValid(ItemToAdd) == false"));
		return;
	}
	UStoredItemInfo* ItemInfo = UStoredItemInfo::GenerateStorageInfoForItem(ItemToAdd);
	ItemToAdd->Destroy();
	if (IsValid(ItemInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UStorageComponent::PlaceItem IsValid(ItemInfo) == false"));
		return;
	}
	if (TryPlaceItemAtIndex(ItemInfo, GetIndexByTile(Coordinates)) == true)
	{
		return;
	}
	if (TryPlaceItem(ItemInfo) == true)
	{
		return;
	}
	DropItem(ItemInfo);
	
}

void UStorageComponent::SendUpdatedItems()
{
	TMap<UStoredItemInfo*, FIntPoint> ItemDataToBroadcast = GetAllItems();
	TArray<UStoredItemInfo*> ItemsToBroadcast;
	TArray<FIntPoint> PositionsToBroadcast;
	ItemDataToBroadcast.GenerateKeyArray(ItemsToBroadcast);
	ItemDataToBroadcast.GenerateValueArray(PositionsToBroadcast);
	OnItemsUpdated.ExecuteIfBound(ItemsToBroadcast, PositionsToBroadcast);

	OnFirstItemUpdated.ExecuteIfBound(Items[0]);
}

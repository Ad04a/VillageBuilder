// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/StoredItemInfo.h"
#include "Headers/ItemInfo.h"
#include "Engine/DataTable.h"
#include "StorageComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FItemsUpdatedSignature, TArray<UStoredItemInfo*>, Items, TArray<FIntPoint>, Indexes);
DECLARE_DYNAMIC_DELEGATE_OneParam(FItemSignature, UStoredItemInfo*, Item);

USTRUCT(BlueprintType)
struct FStorageData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Content)
	int Rows;

	UPROPERTY(EditAnywhere, Category = Content)
	int Columns;
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VILLAGEBUILDER_API UStorageComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category = Content)
	UDataTable* StorageDataTable;

	UPROPERTY(EditDefaultsOnly, Category = Content)
	FName RollToRead = "Station";

	UPROPERTY(VisibleAnywhere, Category = Content)
	TArray<class UStoredItemInfo* > Items;

	UPROPERTY(EditAnywhere, Category = Content)
	int Rows;

	UPROPERTY(EditAnywhere, Category = Content)
	int Columns;

	bool IsPositionValid(FIntPoint Position);

	TArray<FIntPoint> GetAllTiles(FIntPoint ItemSlots, int DesiredPosition);

	bool CanPlace(FIntPoint ItemSlots, int DesiredPosition);

	FIntPoint GetTileByIndex(int Index);
	int GetIndexByTile(FIntPoint InTile);

	TPair<bool, class UStoredItemInfo*> TryGetItem(int ItemIndex);

	void RemoveItem(class UStoredItemInfo* ItemToRemove);

	void SendUpdatedItems();

	void AddItemAt(UStoredItemInfo* InItemInfo, int PlaceIndex);

public:

	FItemsUpdatedSignature OnItemsUpdated;
	FItemSignature OnFirstItemUpdated;
	FItemSignature OnItemRemoved;

	void Init(TMap<FIntPoint, FItemInfoStruct> SavedItems = TMap<FIntPoint, FItemInfoStruct>());
	TMap<FIntPoint, FItemInfoStruct> GetSaveInfo();
	int GetRows() { return Rows; }
	int GetColumns() { return Columns; }
	TMap<UStoredItemInfo*, FIntPoint> GetAllItems();

	bool TryPlaceItem(UStoredItemInfo* InItemInfo, bool bTryRotating = false);
	bool TryPlaceItemAtIndex(UStoredItemInfo* InItemInfo, int Index);
	UStoredItemInfo* TakeItemByNumeration(int Numeration);
	UStoredItemInfo* TakeItemByClass(TSubclassOf<class AItem> ItemClass);
	void RotateItem(UStoredItemInfo* InItemInfo);

	void Sort(UStoredItemInfo* DesiredEquip = nullptr);
	class AItem* DropItem(UStoredItemInfo* InItemInfo);
	void DropAllItems();
	bool PlaceItem(class AItem* ItemToAdd, FIntPoint Coordinates = FIntPoint(-1,-1), bool TryRotating=true);
	class AItem* DropFirst();
};

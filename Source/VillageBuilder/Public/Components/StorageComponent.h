// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/StoredItemInfo.h"
#include "Engine/DataTable.h"
#include "StorageComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FItemsUpdatedSignature, TArray<UStoredItemInfo*>, Items, TArray<FIntPoint>, Indexes);

USTRUCT(BlueprintType)
struct FStorageInfoStruct
{
	GENERATED_BODY()

	//UPROPERTY()
	//TArray<FItemInfoStruct> Items;

	/*inline bool operator==(const FStorageInfoStruct& other) const
	{
		return (other.Rows == Rows && other.Columns == Columns);
	}
	inline bool operator != (const FStorageInfoStruct& other) const
	{
		return !(other.Rows == Rows && other.Columns == Columns);
	}*/
};

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

public:

	FItemsUpdatedSignature OnItemsUpdated;

	void Init(FStorageInfoStruct InLoadInfo = FStorageInfoStruct());
	FStorageInfoStruct GetSaveInfo();
	bool TryPlaceItem(UStoredItemInfo* InItemInfo);
	void AddItemAt(UStoredItemInfo* InItemInfo, int PlaceIndex);
	int GetRows() { return Rows; }
	int GetColumns() { return Columns; }
	TMap<UStoredItemInfo*, FIntPoint> GetAllItems();


};

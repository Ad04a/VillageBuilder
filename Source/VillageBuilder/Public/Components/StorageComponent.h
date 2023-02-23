// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Engine/DataTable.h"
#include "StorageComponent.generated.h"

USTRUCT(BlueprintType)
struct FStorageRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Content)
	TArray<int> ItemSlots;

	inline bool operator==(const FStorageRow& other) const
	{
		return (other.ItemSlots == ItemSlots);
	}
	inline bool operator != (const FStorageRow& other) const
	{
		return !(other.ItemSlots == ItemSlots);
	}
};

USTRUCT(BlueprintType)
struct FStorageInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FItemInfoStruct> Items;

	UPROPERTY(EditDefaultsOnly, Category = Content)
	TArray<int> LockedSlots;

	UPROPERTY(EditAnywhere, Category = Content)
	TArray<FStorageRow> ItemRows;

	inline bool operator==(const FStorageInfoStruct& other) const
	{
		return (other.Items == Items && other.ItemRows == ItemRows);
	}
	inline bool operator != (const FStorageInfoStruct& other) const
	{
		return !(other.Items == Items && other.ItemRows == ItemRows);
	}
};

USTRUCT(BlueprintType)
struct FStorageData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Content)
	TArray<FStorageRow> ItemRows;
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
	TArray<FItemInfoStruct> Items;

	UPROPERTY(VisibleAnywhere, Category = Content)
	TArray<int> LockedSlots;

	UPROPERTY(VisibleAnywhere, Category = Content)
	TArray<FStorageRow> ItemRows;

	TPair<int, int> CanPlace(AItem* ItemToPlace, TPair<int, int> DesiredPosition = TPair<int, int>());

public:
	void Init(FStorageInfoStruct InLoadInfo = FStorageInfoStruct());
	FStorageInfoStruct GetSaveInfo();
	bool PlaceItem(AItem* InItem);


};

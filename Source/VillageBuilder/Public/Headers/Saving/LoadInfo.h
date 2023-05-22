#pragma once

#include "Headers/StatAndTraitStructure.h"
#include "Headers/ItemInfo.h"
#include "LoadInfo.generated.h"

USTRUCT(BlueprintType)
struct FVillagerLoadInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	FString Name = "Name";

	UPROPERTY()
	TMap<TEnumAsByte<ETrait>, FTraitInfoStruct> TraitsMap;

	UPROPERTY()
	TMap<TEnumAsByte<EStat>, FStatInfoStruct> StatsMap;

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	TMap<FIntPoint, FItemInfoStruct> InventoryInfo;

	UPROPERTY()
	unsigned int ID = 0;

	inline bool operator==(const FVillagerLoadInfoStruct& other) const
	{
		return other.Name == Name && other.Transform.GetLocation() == Transform.GetLocation();
	}
	inline bool operator != (const FVillagerLoadInfoStruct& other) const
	{
		return !(other.Name == Name && other.Transform.GetLocation() == Transform.GetLocation());
	}
};
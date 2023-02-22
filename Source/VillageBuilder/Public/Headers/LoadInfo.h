#pragma once

#include "Headers/StatAndTraitStructure.h"
#include "Headers/ItemInfo.h"

#include "LoadInfo.generated.h"

USTRUCT(BlueprintType)
struct FVillagerLoadInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	FString Name;

	UPROPERTY()
	TMap<TEnumAsByte<ETrait>, FTraitInfoStruct> TraitsMap;

	UPROPERTY()
	TMap<TEnumAsByte<EStat>, FStatInfoStruct> StatsMap;

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	FItemInfoStruct HoldingItem = FItemInfoStruct();

	UPROPERTY()
	int ID = -1;

	inline bool operator==(const FVillagerLoadInfoStruct& other) const
	{
		return other.Name == Name && other.Transform.GetLocation() == Transform.GetLocation();
	}
	inline bool operator != (const FVillagerLoadInfoStruct& other) const
	{
		return !(other.Name == Name && other.Transform.GetLocation() == Transform.GetLocation());
	}
};
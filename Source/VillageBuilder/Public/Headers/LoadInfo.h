#pragma once

#include "Headers/StatAndTraitStructure.h"
#include "Headers/ItemInfo.h"

#include "LoadInfo.generated.h"

USTRUCT(BlueprintType)
struct FLoadInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	FName Name;

	UPROPERTY()
	TMap<TEnumAsByte<EStat>, FStatInfoStruct> StatsMap;

	UPROPERTY()
	TMap<TEnumAsByte<ETrait>, FTraitInfoStruct> TraitsMap;

	//UPROPERTY()
	//TMap<TEnumAsByte<EVillagerItemSlot>, FItemInfoStruct> ItemSlots;

	UPROPERTY()
	FTransform Transform;
	/*, InWorkPlace*/

	inline bool operator==(const FLoadInfoStruct& other) const
	{
		return other.Name == Name && other.Transform.GetLocation() == Transform.GetLocation();
	}
	inline bool operator != (const FLoadInfoStruct& other) const
	{
		return !(other.Name == Name && other.Transform.GetLocation() == Transform.GetLocation());
	}
};
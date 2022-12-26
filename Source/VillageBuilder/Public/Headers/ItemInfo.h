#pragma once

#include "ItemInfo.generated.h"

UENUM(BlueprintType)
enum EItemType {
	OneHanded  UMETA(DisplayName = "OneHanded"),
	TwoHanded  UMETA(DisplayName = "TwoHanded"),
	Attachable UMETA(DisplayName = "Attachable"),

};

USTRUCT(BlueprintType)
struct FItemInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<AActor> ItemClass;

	inline bool operator==(const FItemInfoStruct& other) const
	{
		return other.ItemClass == ItemClass;
	}
	inline bool operator != (const FItemInfoStruct& other) const
	{
		return !(other.ItemClass == ItemClass);
	}
};
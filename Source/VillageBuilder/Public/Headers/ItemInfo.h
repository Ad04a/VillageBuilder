#pragma once

#include "Engine/DataTable.h"
#include "ItemInfo.generated.h"

UENUM(BlueprintType)
enum EItemType {
	None       UMETA(DisplayName = "None"),
	Tool       UMETA(DisplayName = "Tool"),
	Consumable UMETA(DisplayName = "Consumable")

};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText DisplayName;

	UPROPERTY(EditAnywhere, meta = (Multiline = true))
	FText Description;

	UPROPERTY(EditAnywhere)
	float Weight;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EItemType> ItemType;

};

USTRUCT(BlueprintType)
struct FItemInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<AActor> ItemClass;

	UPROPERTY()
	FString SerializedItem = "";

	inline bool operator==(const FItemInfoStruct& other) const
	{
		return other.ItemClass == ItemClass;
	}
	inline bool operator != (const FItemInfoStruct& other) const
	{
		return !(other.ItemClass == ItemClass);
	}
};
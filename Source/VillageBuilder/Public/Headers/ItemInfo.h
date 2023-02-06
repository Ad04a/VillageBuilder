#pragma once

#include "Engine/DataTable.h"
#include "ItemInfo.generated.h"

UENUM(BlueprintType)
enum EItemType {
	Default     UMETA(DisplayName = "Default"),
	Axe         UMETA(DisplayName = "Axe"),
	Pickaxe 	UMETA(DisplayName = "Pickaxe"),
	Food		UMETA(DisplayName = "Food"),
	Drink		UMETA(DisplayName = "Drink"),
	BuilderItem UMETA(DisplayName = "BuilderItem")

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

	UPROPERTY(EditAnywhere)
	UAnimMontage* ItemAnimMontage;

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

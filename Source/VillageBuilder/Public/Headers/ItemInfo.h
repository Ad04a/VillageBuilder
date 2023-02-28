#pragma once

#include "Engine/DataTable.h"
//#include "Headers/InventoryInfos.h"
#include "ItemInfo.generated.h"

UENUM(BlueprintType)
enum EItemType {
	Default     UMETA(DisplayName = "Default"),
	Axe         UMETA(DisplayName = "Axe"),
	Pickaxe 	UMETA(DisplayName = "Pickaxe"),
	Food		UMETA(DisplayName = "Food"),
	Drink		UMETA(DisplayName = "Drink"),
	BuilderItem UMETA(DisplayName = "BuilderItem"),
	Log			UMETA(DisplayName = "Log")

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
	FIntPoint Slots;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EItemType> ItemType;

	UPROPERTY(EditAnywhere)
	UAnimMontage* ItemAnimMontage;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* Icon;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* IconRotated;

};

USTRUCT(BlueprintType)
struct FItemInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<AActor> ItemClass;

	UPROPERTY()
	FString SerializedItem = "";

	UPROPERTY()
	FTransform Transform;

	inline bool operator==(const FItemInfoStruct& other) const
	{
		return (other.ItemClass == ItemClass && other.Transform.GetLocation() == Transform.GetLocation());
	}
	inline bool operator != (const FItemInfoStruct& other) const
	{
		return !(other.ItemClass == ItemClass && other.Transform.GetLocation() == Transform.GetLocation());
	}
};

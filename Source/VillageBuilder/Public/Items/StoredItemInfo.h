#pragma once

//
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Headers/ItemInfo.h"
#include "StoredItemInfo.generated.h"

UCLASS(BlueprintType)
class VILLAGEBUILDER_API UStoredItemInfo : public UObject
{
	GENERATED_BODY()

protected:
	FItemInfoStruct ItemInfo;
	FIntPoint Slots;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* Icon;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* IconRotated;

public:
	bool bRotated = false;

	static UStoredItemInfo* GenerateStorageInfoForItem(class AItem* InItem);
	FItemInfoStruct GetItemInfo() {return ItemInfo;}
	void SetSlots(FIntPoint Dimensions) { Slots = Dimensions; }
	FIntPoint GetSlots() { return Slots; }
	UMaterialInterface* GetIcon() { return bRotated ? IconRotated : Icon; }
};
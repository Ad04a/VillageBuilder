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
	static UStoredItemInfo* GenerateStorageInfoForItem(class AItem* InItem);
	FItemInfoStruct GetItemInfo() {return ItemInfo;}
	FIntPoint GetSlots() { return Slots; }
	UMaterialInterface* GetIcon() { return Icon; }
};
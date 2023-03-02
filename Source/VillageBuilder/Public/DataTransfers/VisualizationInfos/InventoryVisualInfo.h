// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTransfers/VisualizationInfo.h"
#include "InventoryVisualInfo.generated.h"

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FSendRecivedItemsSignature, TArray<class UMaterialInterface*>, Icons, TArray<FIntPoint>, Sizes, TArray<FIntPoint>, Indexes);

UCLASS()
class VILLAGEBUILDER_API UInventoryVisualInfo : public UVisualizationInfo
{
	GENERATED_BODY()
protected:
	class UStorageComponent* Storage;

	UFUNCTION()
	void RecieveUpdatedItems(TArray<class UStoredItemInfo*> Items, TArray<FIntPoint> Indexes);

public:
	UFUNCTION()
	UObject* GetItemFromStorage(int Index);

	UFUNCTION()
	void OnDragItemDropped(UObject* DroppedObject , int Index);

	UFUNCTION()
	void DropItem(UObject* DroppedObject);

	FSendRecivedItemsSignature OnItemsUpdated;

	static UVisualizationInfo* CreateVisualInfo(AActor* InActor);
	virtual void Clear() override;
	FVector2D GetSize();
	void InvokeInitial();
};

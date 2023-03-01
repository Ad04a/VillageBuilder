// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/InventoryVisualInfo.h"
#include "Characters/Villager.h"
#include "WorkSystem/BaseWorkStation.h"
#include "Components/StorageComponent.h"

UVisualizationInfo* UInventoryVisualInfo::CreateVisualInfo(AActor* InActor)
{
	UInventoryVisualInfo* Info = NewObject<UInventoryVisualInfo>();
	if (IsValid(Info) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryVisualInfo::CreateVisualInfo Cannot create info for %s of class %s"), *InActor->GetName(), *InActor->GetClass()->GetName());
		return nullptr;
	}
	AVillager* Villager = Cast<AVillager>(InActor);
	if (IsValid(Villager) == true)
	{
		Info->Storage = Villager->GetStorageComponent();
	}
	ABaseWorkStation* WorkStation = Cast<ABaseWorkStation>(InActor);
	if (IsValid(WorkStation) == true)
	{
		Info->Storage = Villager->GetStorageComponent();
	}
	Info->Storage->OnItemsUpdated.BindDynamic(Info, &UInventoryVisualInfo::RecieveUpdatedItems);
	return Info;
}

FVector2D UInventoryVisualInfo::GetSize()
{
	return FVector2D(Storage->GetColumns(), Storage->GetRows());
}

void UInventoryVisualInfo::RecieveUpdatedItems(TArray<UStoredItemInfo*> Items, TArray<FIntPoint> Indexes)
{
	TArray<UMaterialInterface*> Icons;
	TArray<FIntPoint> Sizes;
	for (int i = 0; i < Items.Num(); i++)
	{
		Icons.Add(Items[i]->GetIcon());
		Sizes.Add(Items[i]->GetSlots());
	}
	OnItemsUpdated.ExecuteIfBound(Icons, Sizes, Indexes);
}

void UInventoryVisualInfo::InvokeInitial()
{
	TArray<UStoredItemInfo*> Items; 
	TArray<FIntPoint> Indexes;
	Storage->GetAllItems().GenerateKeyArray(Items);
	Storage->GetAllItems().GenerateValueArray(Indexes);
	RecieveUpdatedItems(Items, Indexes);
}

UObject* UInventoryVisualInfo::GetItemFromStorage(int Index)
{
	return Cast<UObject>(Storage->TakeItemByNumeration(Index));
}

void UInventoryVisualInfo::OnDragItemDropped(UObject* DroppedObject, int Index)
{
	UStoredItemInfo* Item = Cast<UStoredItemInfo>(DroppedObject);
	if (IsValid(Item) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryVisualInfo::OnDragItemDropped Given DropInfo is not of type UStoredItemInfo"));
	}
	if (Storage->TryPlaceItemAtIndex(Item, Index) == true)
	{
		return;
	}
	if (Storage->TryPlaceItem(Item) == true)
	{
		return;
	}
}

void UInventoryVisualInfo::Clear()
{
	Super::Clear();
	Storage = nullptr;
}
#include "Items/StoredItemInfo.h"
#include "Items/Item.h"

UStoredItemInfo* UStoredItemInfo::GenerateStorageInfoForItem(AItem* InItem)
{
	UStoredItemInfo* Info = NewObject<UStoredItemInfo>();
	if (IsValid(Info) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UStoredItemInfo::GenerateStorageInfoForItem Cannot create info"));
		return nullptr;
	}
	if (IsValid(InItem) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UStoredItemInfo::GenerateStorageInfoForItem Cannot create info IsValid(InItem) == false"));
		return nullptr;
	}
	Info->ItemInfo = InItem->GetSaveInfo();
	Info->Slots = InItem->GetSlots();

	UDataTable* ItemTable = InItem->GetDataTable();
	if (IsValid(ItemTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UStoredItemInfo::LoadFromDataTable() IsValid(DataTable) == false from %s"), *InItem->GetClass()->GetName());
		return nullptr;
	}

	FItemData* ItemData = ItemTable->FindRow<FItemData>(InItem->GetClass()->GetFName(), "");

	if (ItemData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UStoredItemInfo::LoadFromDataTable() ItemData == nullptr from %s"), *InItem->GetClass()->GetName());
		return nullptr;
	}

	Info->Icon = ItemData->Icon;
	Info->IconRotated = ItemData->IconRotated;
	return Info;
}
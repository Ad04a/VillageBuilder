// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Tasks/BTT_EquipRightItems.h"
#include "AI/Villager/Managements/WorkerManager.h"
#include "AI/Villager/VillagerAIController.h"
#include "Characters/Villager.h"
#include "WorkSystem/BaseWorkStation.h"
#include "Components/StorageComponent.h"
#include "Items/StoredItemInfo.h"


UBTT_EquipRightItems::UBTT_EquipRightItems()
{
	NodeName = "EquipRightItems";
}

EBTNodeResult::Type UBTT_EquipRightItems::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_EquipRightItems::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_EquipRightItems::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	UWorkerManager* WorerkService = Controller->WorkManager;
	if (IsValid(WorerkService) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_EquipRightItems::ExecuteTask IsValid(WorkService) == falses"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	ABaseWorkStation* WorkStationActor = Cast<ABaseWorkStation>(BlackBoard->GetValueAsObject(WorkStation.SelectedKeyName));
	if (IsValid(WorkStationActor) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_EquipRightItems::ExecuteTask IsValid(WorkStationActor) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	AVillager* Villager = Controller->GetControlledVillager();
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_EquipRightItems::ExecuteTask IsValid(Villager) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	UStorageComponent* WorkStationStorage = WorkStationActor->GetStorageComponent();
	UStorageComponent* VillagerStorage	  = Villager->GetStorageComponent();

	TArray<UStoredItemInfo*> BufferedItems;

	TMap<UStoredItemInfo*, FIntPoint> VillagerItems = VillagerStorage->GetAllItems();
	TArray<TSubclassOf<AItem >> NeededClasses = WorerkService->GetNeededItemClasses();

	for (int i = VillagerItems.Num()-1; i >= 0 ; i--)
	{
		UStoredItemInfo* Item = VillagerStorage->TakeItemByNumeration(i);
		if (IsValid(Item) == false)
		{
			continue;
		}
		TSubclassOf<AItem> ItemClass = Item->GetItemInfo().ItemClass;
		bool Check = false;
		for (TSubclassOf<AItem> TempClass : NeededClasses)
		{
			if (ItemClass->IsChildOf(TempClass))
			{
				UE_LOG(LogTemp, Error, TEXT("Vleze"));
				Check = true;
				ItemClass = TempClass;
				break;
			}
		}
		if (Check == true)
		{		
			NeededClasses.RemoveSingle(ItemClass);
			VillagerStorage->TryPlaceItem(Item, true);
			continue;
		}
		BufferedItems.Add(Item);
	}
	

	for (TSubclassOf<class AItem > ItemClass : NeededClasses)
	{
		UStoredItemInfo* Item = WorkStationStorage->TakeItemByClass(ItemClass);
		if (Item == nullptr)
		{
			continue;
		}
		BufferedItems.Add(Item);
	}

	BufferedItems.Sort([](UStoredItemInfo& Item1, UStoredItemInfo& Item2) {
		return (Item1.GetSlots().X * Item1.GetSlots().Y) > (Item2.GetSlots().X * Item2.GetSlots().Y);
		});

	VillagerStorage->Sort();
	WorkStationStorage->Sort();
	NeededClasses = WorerkService->GetNeededItemClasses();

	for (UStoredItemInfo* Item : BufferedItems)
	{
		TSubclassOf<AItem> ItemClass = Item->GetItemInfo().ItemClass;
		bool Check = false;
		for (TSubclassOf<AItem> TempClass : NeededClasses)
		{
			if (ItemClass->IsChildOf(TempClass))
			{
				Check = true;
				ItemClass = TempClass;
				break;
			}
		}
		if (Check == true)
		{
			if (VillagerStorage->TryPlaceItem(Item, true) == true)
			{
				continue;
			}
			WorkStationStorage->TryPlaceItem(Item, true);
			continue;
		}
		if (WorkStationStorage->TryPlaceItem(Item, true) == true) 
		{
			continue;
		}
		VillagerStorage->TryPlaceItem(Item, true);
		
	}
	if (NotifyIfFull == false)
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	bool IsInventorySame = !VillagerItems.IsEmpty();
	TMap<UStoredItemInfo*, FIntPoint> NewItems = VillagerStorage->GetAllItems();
	for (TPair<UStoredItemInfo*, FIntPoint> Item : VillagerItems)
	{
		IsInventorySame = IsInventorySame && NewItems.Contains(Item.Key);
	}
	BlackBoard->SetValueAsBool(IsFull.SelectedKeyName, IsInventorySame);

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}


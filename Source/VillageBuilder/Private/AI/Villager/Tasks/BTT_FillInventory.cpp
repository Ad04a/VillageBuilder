// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Tasks/BTT_FillInventory.h"
#include "AI/Villager/VillagerAIController.h"
#include "Characters/Villager.h"
#include "WorkSystem/BaseWorkStation.h"
#include "Components/StorageComponent.h"
#include "Items/StoredItemInfo.h"

UBTT_FillInventory::UBTT_FillInventory()
{
	NodeName = TEXT("FillInventory");
}

EBTNodeResult::Type UBTT_FillInventory::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
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
	UStorageComponent* VillagerStorage = Villager->GetStorageComponent();

	TMap<UStoredItemInfo*, FIntPoint> WorkStationItems = WorkStationStorage->GetAllItems();

	for (int i = WorkStationItems.Num() - 1; i >= 0; i--)
	{
		UStoredItemInfo* Item = WorkStationStorage->TakeItemByNumeration(i);

		if (VillagerStorage->TryPlaceItem(Item, true) == false)
		{
			WorkStationStorage->TryPlaceItem(Item, true);
			break;
		}
	}

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}


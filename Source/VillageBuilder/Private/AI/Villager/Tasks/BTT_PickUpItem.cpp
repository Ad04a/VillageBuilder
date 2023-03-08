// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Tasks/BTT_PickUpItem.h"
#include "AI/Villager/VillagerAIController.h"
#include "Characters/Villager.h"
#include "Components/StorageComponent.h"
#include "Items/Item.h"

UBTT_PickUpItem::UBTT_PickUpItem()
{
	NodeName = "PickUpItem";
}

EBTNodeResult::Type UBTT_PickUpItem::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_PickUpItem::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_PickUpItem::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	AVillager* Villager = Controller->GetControlledVillager();
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_PickUpItem::ExecuteTask IsValid(Villager) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UStorageComponent* VillagerStorage = Villager->GetStorageComponent();

	AItem* ItemToEquip = Cast<AItem>(BlackBoard->GetValueAsObject(TargetItem.SelectedKeyName));
	if (IsValid(ItemToEquip) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_PickUpItem::ExecuteTask IsValid(ItemToEquip) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	bool bSuccess = VillagerStorage->PlaceItem(ItemToEquip);

	BlackBoard->SetValueAsBool(IsFull.SelectedKeyName, !bSuccess);

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}
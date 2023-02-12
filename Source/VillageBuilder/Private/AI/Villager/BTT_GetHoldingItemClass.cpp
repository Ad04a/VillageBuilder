// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/BTT_GetHoldingItemClass.h"

UBTT_GetHoldingItemClass::UBTT_GetHoldingItemClass()
{
	NodeName = "GetHoldingItemClass";
}

EBTNodeResult::Type UBTT_GetHoldingItemClass::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetHoldingItemClass::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetHoldingItemClass::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	AVillager* Villager = Controller->GetControlledVillager();
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetHoldingItemClass::ExecuteTask IsValid(Villager) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	AItem* HoldingItem = Villager->GetItem();
	if (IsValid(HoldingItem) == false)
	{
		BlackBoard->ClearValue(GetSelectedBlackboardKey());
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);

		return EBTNodeResult::Succeeded;
	}
	BlackBoard->SetValueAsClass(GetSelectedBlackboardKey(), HoldingItem->GetClass());
	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/BTT_GetMemorizedItem.h"

UBTT_GetMemorizedItem::UBTT_GetMemorizedItem()
{
	NodeName = "GetMemorizedItem";
}

EBTNodeResult::Type UBTT_GetMemorizedItem::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_GetLocationOfObject::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_GetLocationOfObject::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UObject* MemorizedObject = Controller->GetFirstRemembered();
	if (IsValid(MemorizedObject) == false)
	{
		BlackBoard->ClearValue(GetSelectedBlackboardKey());
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);

		return EBTNodeResult::Succeeded;
	}
	BlackBoard->SetValueAsObject(GetSelectedBlackboardKey(), MemorizedObject);
	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GeneralTasks/BTT_SetEnumValue.h"

UBTT_SetEnumValue::UBTT_SetEnumValue()
{
	NodeName = TEXT("SetEnumValue");
}

EBTNodeResult::Type UBTT_SetEnumValue::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{

	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_SetEnumValue::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_SetEnumValue::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	BlackBoard->SetValueAsEnum(GetSelectedBlackboardKey(), SetToValue);

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}

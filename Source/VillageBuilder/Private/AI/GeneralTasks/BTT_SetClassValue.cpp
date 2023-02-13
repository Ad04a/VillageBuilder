// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GeneralTasks/BTT_SetClassValue.h"

UBTT_SetClassValue::UBTT_SetClassValue()
{
	NodeName = TEXT("SetClassValue");
}

EBTNodeResult::Type UBTT_SetClassValue::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{

	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_SetClassValue::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_SetClassValue::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	BlackBoard->SetValueAsClass(GetSelectedBlackboardKey(), SelectedClass);

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}

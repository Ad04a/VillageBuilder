// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GeneralDecorator/BTD_ConditionalLoopForClassCompare.h"

UBTD_ConditionalLoopForClassCompare::UBTD_ConditionalLoopForClassCompare()
{
	NodeName = "ConditionalLoopForClassCompare()";
}

bool UBTD_ConditionalLoopForClassCompare::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComponent, NodeMemory);
	if (bSuccess == false)
	{
		return false;
	}
	AGeneralAIController* Controller = Cast<AGeneralAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_GetLocationOfObject::CalculateRawConditionValue IsValid(Controller) == false"));
		return false;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_GetLocationOfObject::CalculateRawConditionValue IsValid(BlackBoard) == false"));
		return false;
	}
	if (InverseCondition) {
		return BlackBoard->GetValueAsClass(CompareWith.SelectedKeyName) != BlackBoard->GetValueAsClass(GetSelectedBlackboardKey());
	}
	return BlackBoard->GetValueAsClass(CompareWith.SelectedKeyName) == BlackBoard->GetValueAsClass(GetSelectedBlackboardKey());
}

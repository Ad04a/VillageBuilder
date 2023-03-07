// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GeneralDecorator/BTD_ConditionalLoopForVectorCompare.h"
#include "AI/GeneralAIController.h"

UBTD_ConditionalLoopForVectorCompare::UBTD_ConditionalLoopForVectorCompare()
{
	NodeName = "BTD_ConditionalLoopForVectorCompare";
}

bool UBTD_ConditionalLoopForVectorCompare::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComponent, NodeMemory);
	if (bSuccess == false)
	{
		return false;
	}
	AGeneralAIController* Controller = Cast<AGeneralAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTD_ConditionalLoopForVectorCompare::CalculateRawConditionValue IsValid(Controller) == false"));
		return false;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTD_ConditionalLoopForVectorCompare::CalculateRawConditionValue IsValid(BlackBoard) == false"));
		return false;
	}
	if (InverseCondition) {
		return BlackBoard->GetValueAsVector(CompareWith.SelectedKeyName) != BlackBoard->GetValueAsVector(GetSelectedBlackboardKey());
	}
	return BlackBoard->GetValueAsVector(CompareWith.SelectedKeyName) == BlackBoard->GetValueAsVector(GetSelectedBlackboardKey());
}

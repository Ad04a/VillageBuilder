// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GeneralDecorator/BTD_ConditionalLoopForKey.h"

UBTD_ConditionalLoopForKey::UBTD_ConditionalLoopForKey()
{
	NodeName = "ConditionalLoopForBoolKey()";
}

bool UBTD_ConditionalLoopForKey::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComponent, NodeMemory);
	if (bSuccess == false)
	{
		return false;
	}
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTD_ConditionalLoopForKey::CalculateRawConditionValue IsValid(Controller) == false"));
		return false;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTD_ConditionalLoopForKey::CalculateRawConditionValue IsValid(BlackBoard) == false"));
		return false;
	}
	bool bChecker = BlackBoard->GetValueAsBool(GetSelectedBlackboardKey());
	return bChecker == CheckValue;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GeneralDecorator/BTD_CheckBoolValue.h"

UBTD_CheckBoolValue::UBTD_CheckBoolValue()
{
	NodeName = "CheckBoolValue";
}

bool UBTD_CheckBoolValue::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComponent, NodeMemory);
	if (bSuccess == false)
	{
		return false;
	}
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
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
	bool bChecker = BlackBoard->GetValueAsBool(GetSelectedBlackboardKey());
	return bChecker == CheckValue;
}
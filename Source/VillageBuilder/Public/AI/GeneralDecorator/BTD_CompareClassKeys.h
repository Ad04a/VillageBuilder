// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AI/GeneralAIController.h"

#include "BTD_CompareClassKeys.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTD_CompareClassKeys : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector CompareWith;
public:
	UBTD_CompareClassKeys();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) const override;
};

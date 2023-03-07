// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Decorators/BTDecorator_ConditionalLoop.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "BTD_ConditionalLoopForVectorCompare.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTD_ConditionalLoopForVectorCompare : public UBTDecorator_ConditionalLoop
{
	GENERATED_BODY()
public:
	UBTD_ConditionalLoopForVectorCompare();
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector CompareWith;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	bool InverseCondition;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) const override;
};

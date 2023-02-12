// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Decorators/BTDecorator_ConditionalLoop.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AI/Villager/VillagerAIController.h"

#include "BTD_ConditionalLoopForClassCompare.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTD_ConditionalLoopForClassCompare : public UBTDecorator_ConditionalLoop
{
	GENERATED_BODY()
public:
	UBTD_ConditionalLoopForClassCompare();
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector CompareWith;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	bool InverseCondition;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) const override;
};

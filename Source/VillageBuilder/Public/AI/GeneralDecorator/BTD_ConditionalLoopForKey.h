// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Decorators/BTDecorator_ConditionalLoop.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AI/Villager/VillagerAIController.h"

#include "BTD_ConditionalLoopForKey.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTD_ConditionalLoopForKey : public UBTDecorator_ConditionalLoop
{
	GENERATED_BODY()
public:
	UBTD_ConditionalLoopForKey();
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	bool CheckValue = false;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) const override;
};

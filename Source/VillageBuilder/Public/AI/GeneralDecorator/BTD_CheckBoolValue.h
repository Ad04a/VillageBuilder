// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AI/Villager/VillagerAIController.h"

#include "BTD_CheckBoolValue.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTD_CheckBoolValue : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTD_CheckBoolValue();
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	bool CheckValue = false;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) const override;
};

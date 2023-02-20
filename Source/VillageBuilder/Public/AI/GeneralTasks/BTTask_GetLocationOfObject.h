// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AI/GeneralAIController.h"

#include "BTTask_GetLocationOfObject.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTTask_GetLocationOfObject : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector WriteInto;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	float SearchRadius;

public:
	UBTTask_GetLocationOfObject();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

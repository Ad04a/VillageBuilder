// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AI/GeneralAIController.h"

#include "BTT_RandomPointInRadius.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTT_RandomPointInRadius : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector WriteInto;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	float SearchRadius;

public:
	UBTT_RandomPointInRadius();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

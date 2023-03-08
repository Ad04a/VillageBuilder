// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_PickUpItem.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTT_PickUpItem : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector TargetItem;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector IsFull;

public:
	UBTT_PickUpItem();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

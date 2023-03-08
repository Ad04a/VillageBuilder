// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_EquipRightItems.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTT_EquipRightItems : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector WorkStation;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector IsFull;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	bool NotifyIfFull;

public:
	UBTT_EquipRightItems();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

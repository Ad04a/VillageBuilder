// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_FindClosestOfFoliage.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTT_FindClosestOfFoliage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector WriteInto;

	UPROPERTY(EditAnywhere, Category = Foliage)
	FName TagToSearch;

public:
	UBTT_FindClosestOfFoliage();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_BuildTargetedComponents.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTT_BuildTargetedComponents : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:

public:
	UBTT_BuildTargetedComponents();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

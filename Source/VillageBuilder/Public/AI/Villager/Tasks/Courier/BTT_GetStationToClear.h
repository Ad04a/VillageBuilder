// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_GetStationToClear.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTT_GetStationToClear : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:

public:
	UBTT_GetStationToClear();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

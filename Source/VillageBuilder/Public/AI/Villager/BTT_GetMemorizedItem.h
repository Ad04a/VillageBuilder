// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AI/Villager/VillagerAIController.h"

#include "BTT_GetMemorizedItem.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTT_GetMemorizedItem : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_GetMemorizedItem();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "AI/Villager/VillagerAIController.h"
#include "Headers/VillagerBBKeys.h"
#include "Headers/Interfaces/Interactable.h"

#include "BTTask_InteractWithObject.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTTask_InteractWithObject : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_InteractWithObject();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AI/Villager/VillagerAIController.h"

#include "BTT_GetTargetBuildingComponent.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTT_GetTargetBuildingComponent : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector WorkStationKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector WriteInto;
public:
	UBTT_GetTargetBuildingComponent();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

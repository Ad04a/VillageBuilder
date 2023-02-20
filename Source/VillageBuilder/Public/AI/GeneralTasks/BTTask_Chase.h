// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AI/GeneralAIController.h"
#include "Headers/VillagerBBKeys.h"

#include "BTTask_Chase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTTask_Chase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_Chase();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

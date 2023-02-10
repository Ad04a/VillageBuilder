// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AI/Villager/VillagerAIController.h"

#include "BTS_ResetBackboard.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTS_ResetBackboard : public UBTService
{
	GENERATED_BODY()
public:
	UBTS_ResetBackboard();
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	TArray<struct FBlackboardKeySelector> KeysToClear;

	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)override;
};

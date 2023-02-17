// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AI/Villager/VillagerAIController.h"

#include "BTS_LookForItems.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTS_LookForItems : public UBTService
{
	GENERATED_BODY()
public:
	UBTS_LookForItems();
private:
	UWorld* World;
	AVillagerAIController* Controller;
	UBlackboardComponent* BlackBoard;
	AVillager* Villager;
protected:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector WriteInto;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	TSubclassOf<AActor> SearchClass;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	float SearchRadius;

	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)override;
	void TickNode(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory,float DeltaSeconds)override;
};

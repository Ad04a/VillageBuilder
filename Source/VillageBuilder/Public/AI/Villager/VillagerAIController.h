// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h" 
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "VillagerAIController.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API AVillagerAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AVillagerAIController();
	void BeginPlay() override;
	void OnPossess(APawn* const InPawn)override;
	class UBlackboardComponent* GetBlackboard()const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* Blackboard;
public:
	void SetBehavior(UBehaviorTree* InBehaviorTree);


};

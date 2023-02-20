// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h" 
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "GeneralAIController.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API AGeneralAIController : public AAIController
{
	GENERATED_BODY()
public:
	AGeneralAIController();
	void BeginPlay() override;
	void OnPossess(APawn* const InPawn)override;
	class UBlackboardComponent* GetBlackboard()const;
	void SetBehavior(UBehaviorTree* InBehaviorTree);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* Blackboard;

	class UAISenseConfig_Sight* SightConfig;

	void SetupPerceptionSystem();

	UFUNCTION()
	virtual void ActorDetected(AActor* Actor, struct FAIStimulus const Stimulus);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/Villager.h" 
#include "BehaviorTree/BehaviorTreeComponent.h" 
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
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

	AVillager* ControlledVillager = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* Blackboard;

	class UAISenseConfig_Sight* SightConfig;

	void SetupPerceptionSystem();

	UFUNCTION()
	void ActorDetected(AActor* Actor, struct FAIStimulus const Stimulus);

	UPROPERTY(VisibleAnywhere, Category = Blackboard)
	TArray<AActor*> RememberedActors;

public:
	void SetBehavior(UBehaviorTree* InBehaviorTree);
	AVillager* GetControlledVillager()const;
	void AddRememberdActor(AActor* InActor);
	AActor* GetFirstRememebred();
	TArray<AActor*> GetRememberdActors() const{ return RememberedActors; }
};

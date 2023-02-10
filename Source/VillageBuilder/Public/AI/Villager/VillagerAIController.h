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

	UPROPERTY(VisibleAnywhere)
	TSet<UObject*> RememberedItems;

	UFUNCTION()
	void ActorDetected(AActor* Actor, struct FAIStimulus const Stimulus);

public:
	void SetBehavior(UBehaviorTree* InBehaviorTree);
	AVillager* GetControlledVillager()const;
	UObject* GetFirstRemembered();
};

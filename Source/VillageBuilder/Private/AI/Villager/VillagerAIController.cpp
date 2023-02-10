// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/VillagerAIController.h"
#include "Headers/VillagerBBKeys.h"


AVillagerAIController::AVillagerAIController() 
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComponent"));
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void AVillagerAIController::BeginPlay()
{
	Super::BeginPlay();
	SetBehavior(BehaviorTree);
}

void AVillagerAIController::SetBehavior(UBehaviorTree* InBehaviorTree)
{
	if (IsValid(InBehaviorTree) == false) {
		return;
	}
	BehaviorTree = InBehaviorTree;
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComponent->StartTree(*BehaviorTree);
}

void AVillagerAIController::OnPossess(APawn* const InPawn) 
{
	Super::OnPossess(InPawn);
	if (IsValid(Blackboard) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillagerAIController::OnPossess IsValid(Blackboard) == false"));
	}
	Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	InPawn->bUseControllerRotationYaw = false;
}

UBlackboardComponent* AVillagerAIController::GetBlackboard()const
{
	return Blackboard;
}

AVillager* AVillagerAIController::GetControlledVillager()const 
{
	return Cast<AVillager>(GetPawn()); 
}
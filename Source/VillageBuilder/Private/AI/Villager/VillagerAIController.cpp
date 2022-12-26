// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/VillagerAIController.h"
#include "Headers/VillagerBBKeys.h"


AVillagerAIController::AVillagerAIController() {
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>TempBTree(TEXT("BehaviorTree'/Game/Blueprints/AI/Villager/Villager_BT.Villager_BT'"));
	if (TempBTree.Succeeded() == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillagerAIController::TempBTree.Succeeded() == false"));	
	}
	BTree = TempBTree.Object;
	BTree_component = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComponent"));
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	
}

void AVillagerAIController::BeginPlay() {
	Super::BeginPlay();
	RunBehaviorTree(BTree);
	BTree_component->StartTree(*BTree);
}

void AVillagerAIController::OnPossess(APawn* const InPawn) {
	Super::OnPossess(InPawn);
	if (IsValid(Blackboard) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillagerAIController::OnPossess IsValid(Blackboard) == false"));
	}
	Blackboard->InitializeBlackboard(*BTree->BlackboardAsset);
	InPawn->bUseControllerRotationYaw = false;
}

UBlackboardComponent* AVillagerAIController::GetBlackboard()const {
	return Blackboard;
}
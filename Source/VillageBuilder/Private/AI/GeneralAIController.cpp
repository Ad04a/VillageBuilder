// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GeneralAIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Components/SphereComponent.h"
#include "Headers/VillagerBBKeys.h"


AGeneralAIController::AGeneralAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComponent"));
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	SetupPerceptionSystem();
}

void AGeneralAIController::BeginPlay()
{
	Super::BeginPlay();
	SetBehavior(BehaviorTree);
}

void AGeneralAIController::SetBehavior(UBehaviorTree* InBehaviorTree)
{
	if (IsValid(InBehaviorTree) == false) {
		return;
	}
	BehaviorTree = InBehaviorTree;
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComponent->StartTree(*BehaviorTree);
}

void AGeneralAIController::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
	if (IsValid(Blackboard) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGeneralAIController::OnPossess IsValid(Blackboard) == false"));
	}
	Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	InPawn->bUseControllerRotationYaw = false;
}

void AGeneralAIController::ActorDetected(AActor* Actor, struct FAIStimulus const Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() == false)
	{
		return;
	}
	if (IsValid(Blackboard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGeneralAIController::ActorDetected IsValid(BlackBoard) == false"));
		return;
	}
}

UBlackboardComponent* AGeneralAIController::GetBlackboard()const
{
	return Blackboard;
}
void AGeneralAIController::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	SightConfig->SightRadius = 500.0f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 50.0f;
	SightConfig->PeripheralVisionAngleDegrees = 70.0;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 10.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AGeneralAIController::ActorDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/VillagerAIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Components/SphereComponent.h"
#include "Headers/VillagerBBKeys.h"


AVillagerAIController::AVillagerAIController() 
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComponent"));
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	RememberCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RememberCollision"));
	SetupPerceptionSystem();
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

void AVillagerAIController::ActorDetected(AActor* Actor, struct FAIStimulus const Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() == false)
	{
		return;
	}
	if (IsValid(Blackboard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillagerAIController::ActorDetected IsValid(BlackBoard) == false"));
		return;
	}
	/*AItem* PercievedItem = Cast<AItem>(Actor);
	if (IsValid(PercievedItem) == false)
	{
		return;
	}
	if (PercievedItem->GetItemType() != Blackboard->GetValueAsEnum(VillagerBBKeys::TargetItemType))
	{
		return;
	}
	RememberedItems.Add(Actor);*/
}

UBlackboardComponent* AVillagerAIController::GetBlackboard()const
{
	return Blackboard;
}

AVillager* AVillagerAIController::GetControlledVillager()const 
{
	return Cast<AVillager>(GetPawn()); 
}

void AVillagerAIController::SetupPerceptionSystem()
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
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AVillagerAIController::ActorDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Animals/AnimalAIController.h"
#include "Characters/Villager.h"


void AAnimalAIController::BeginPlay()
{
	if (IsValid(BehaviorDataTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AAnimalAIController::BeginPlay IsValid(DataTable) == false from %s"), *GetPawn()->GetClass()->GetName());
		return;
	}

	FAnimalBehaviorData* BehaviorData = BehaviorDataTable->FindRow<FAnimalBehaviorData>(GetClass()->GetFName(), "");

	if (BehaviorData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AAnimalAIController::BeginPlay ItemData == nullptr from %s"), *GetClass()->GetName());
		return;
	}
	SetBehavior(BehaviorData->BehaviorTree);
}

void AAnimalAIController::ActorDetected(AActor* Actor, struct FAIStimulus const Stimulus)
{
	Super::ActorDetected(Actor, Stimulus);
	if (Actor->IsA(AVillager::StaticClass()) == false)
	{
		return;
	}
	OnVillagerSeen.ExecuteIfBound(Actor->GetActorLocation());
}

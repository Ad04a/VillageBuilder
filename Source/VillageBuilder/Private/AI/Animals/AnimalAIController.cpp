// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Animals/AnimalAIController.h"
#include "Characters/Villager.h"
#include "Characters/Animal.h"


void AAnimalAIController::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
	if (IsValid(InPawn) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AAnimalAIController::OnPossess IsValid(GetPawn()) == false"));
		return;
	}

	if (IsValid(BehaviorDataTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AAnimalAIController::OnPossess IsValid(DataTable) == false from %s"), *InPawn->GetClass()->GetName());
		return;
	}

	FAnimalBehaviorData* BehaviorData = BehaviorDataTable->FindRow<FAnimalBehaviorData>(InPawn->GetClass()->GetFName(), "");

	if (BehaviorData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AAnimalAIController::OnPossess BehaviorDataa == nullptr from %s"), *InPawn->GetClass()->GetName());
		return;
	}
	SetBehavior(BehaviorData->BehaviorTree);
	AAnimal* Animal = Cast<AAnimal>(InPawn);
	if (IsValid(Animal) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AAnimalAIController::OnPossess IsVlaid(Animal) == false"));
		return;
	}
	Animal->OnStateChanged.AddDynamic(this, &AAnimalAIController::UpdateAIState);
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

// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Animals/AnimalAIController.h"
#include "Characters/Villager.h"

void AAnimalAIController::ActorDetected(AActor* Actor, struct FAIStimulus const Stimulus)
{
	Super::ActorDetected(Actor, Stimulus);
	if (Actor->IsA(AVillager::StaticClass()) == false)
	{
		return;
	}
	OnVillagerSeen.ExecuteIfBound(Actor->GetActorLocation());
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/VillagerAIController.h"
#include "Headers/VillagerBBKeys.h"

AVillager* AVillagerAIController::GetControlledVillager()const 
{
	return Cast<AVillager>(GetPawn()); 
}

void AVillagerAIController::AddRememberdActor(AActor* InActor)
{
	RememberedActors.Add(InActor);
}

AActor* AVillagerAIController::GetFirstRememebred()
{
	
	if (RememberedActors.IsEmpty() == true)
	{
		
		return nullptr;
	}
	AActor* TempActor = RememberedActors[0];
	RememberedActors.Remove(TempActor);
	return TempActor;
}


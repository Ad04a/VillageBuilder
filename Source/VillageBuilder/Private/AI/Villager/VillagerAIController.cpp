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

void AVillagerAIController::RegisterAIState(APawn* ControlledPawn, EAIState State)
{
	UpdateAIState(ControlledPawn, State);
}

void AVillagerAIController::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
	ControlledVillager = Cast<AVillager>(InPawn);
	if (IsValid(ControlledVillager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillagerAIController::OnPossess IsValid(ControlledVillager) == false"));
		return;
	}
	ControlledVillager->OnAIStateChanged.AddDynamic(this, &AVillagerAIController::RegisterAIState);
}



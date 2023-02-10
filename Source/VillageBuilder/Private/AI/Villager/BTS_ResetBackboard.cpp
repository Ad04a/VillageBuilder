// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/BTS_ResetBackboard.h"

UBTS_ResetBackboard::UBTS_ResetBackboard()
{
	NodeName = "ResetBackboard";
	bNotifyBecomeRelevant = true;
}

void UBTS_ResetBackboard::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("STANA"));
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetWorkStation::ExecuteTask IsValid(Controller) == false"));
		return;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetWorkStation::ExecuteTask IsValid(BlackBoard) == false"));
		return;
	}
	AVillager* Villager = Controller->GetControlledVillager();
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetWorkStation::ExecuteTask IsValid(Villager) == false"));
		return;
	}
	for (FBlackboardKeySelector Key : KeysToClear)
	{
		BlackBoard->ClearValue(Key.SelectedKeyName);
	}
}
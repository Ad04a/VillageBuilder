// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Services/BTS_WorkerService.h"
#include "AI/Villager/VillagerAIController.h"
#include "GameModes/GameplayModeBase.h"
#include "WorkSystem/VillageManager.h"
#include "WorkSystem/BaseWorkStation.h"

#include "Kismet/GameplayStatics.h"

UBTS_WorkerService::UBTS_WorkerService()
{
	NodeName = "WorkerService";
	bNotifyBecomeRelevant = true;
}

void UBTS_WorkerService::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_WorkerService::OnBecomeRelevant IsValid(Controller) == false"));
		return;
	}
	BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_WorkerService::OnBecomeRelevant IsValid(BlackBoard) == false"));
		return;
	}

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_WorkerService::OnBecomeRelevant IsValid(World) == false"));
		return;
	}

	AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("UBTS_WorkerService::OnBecomeRelevant IsValid(GameMode) == false"));
		return;
	}

	AVillager* Self = Controller->GetControlledVillager();

	Village = GameMode->GetCurrentVillage(Self);
	if (IsValid(Village) == false) {
		UE_LOG(LogTemp, Error, TEXT("UBTS_WorkerService::OnBecomeRelevant IsValid(Village) == false"));
		return;
	}
	ABaseWorkStation* WorkStationActor = Village->GetWorkPlaceFor(Self->ID);
	if (IsValid(WorkStationActor) == false) {
		UE_LOG(LogTemp, Error, TEXT("UBTS_WorkerService::OnBecomeRelevant IsValid(WorkStation) == false"));
		return;
	}

	BlackBoard->SetValueAsObject(WorkService.SelectedKeyName, this);
	BlackBoard->SetValueAsObject(WorkStation.SelectedKeyName, WorkStationActor);
}
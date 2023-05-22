// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Services/BTS_WorkerService.h"
#include "AI/Villager/VillagerAIController.h"
#include "AI/Villager/Managements/WorkerManager.h"
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
	UBlackboardComponent*  BlackBoard = Controller->GetBlackboard();
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

	AVillageManager* Village = GameMode->GetCurrentVillage(Self);
	if (IsValid(Village) == false) {
		UE_LOG(LogTemp, Error, TEXT("UBTS_WorkerService::OnBecomeRelevant IsValid(Village) == false"));
		return;
	}

	BlackBoard->SetValueAsObject(VillageRef.SelectedKeyName, Village);

	ABaseWorkStation* WorkStationActor = Village->GetWorkPlaceFor(Self->ID);
	if (IsValid(WorkStationActor) == false) {
		UE_LOG(LogTemp, Display, TEXT("UBTS_WorkerService::OnBecomeRelevant IsValid(WorkStation) == false Villager is unemployed"));
	}
	if (IsValid(Controller->WorkManager) == true)
	{
		Controller->WorkManager->Clear(Self);
	}
	UWorkerManager* NewManager = UWorkerManager::CreateInstance(this, ManagerClass, Village, BlackBoard, KeysToPassToManager, Self);
	Self->OnDeath.AddDynamic(NewManager, &UWorkerManager::Clear);
	Controller->WorkManager = NewManager;
	BlackBoard->SetValueAsObject(WorkStation.SelectedKeyName, WorkStationActor);
}
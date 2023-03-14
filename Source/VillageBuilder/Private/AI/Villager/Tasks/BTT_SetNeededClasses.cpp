// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Tasks/BTT_SetNeededClasses.h"
#include "AI/Villager/Managements/WorkerManager.h"
#include "AI/Villager/VillagerAIController.h"

UBTT_SetNeededClasses::UBTT_SetNeededClasses()
{
	NodeName = "SetNeededClasses";
}

EBTNodeResult::Type UBTT_SetNeededClasses::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_SetNeededClasses::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_SetNeededClasses::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	UWorkerManager* WorerkService = Controller->WorkManager;
	if (IsValid(WorerkService) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_SetNeededClasses::ExecuteTask IsValid(WorkService) == falses"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	WorerkService->SetNededItemClasses(ClassesToSet);
	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
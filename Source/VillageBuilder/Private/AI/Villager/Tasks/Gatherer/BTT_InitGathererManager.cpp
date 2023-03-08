// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Tasks/Gatherer/BTT_InitGathererManager.h"
#include "AI/Villager/Managements/GathererManager.h"
#include "AI/Villager/VillagerAIController.h"
#include "Characters/Villager.h"

#include "BehaviorTree/BlackboardComponent.h"



UBTT_InitGathererManager::UBTT_InitGathererManager()
{
	NodeName = TEXT("InitGathererManager");
}

EBTNodeResult::Type UBTT_InitGathererManager::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_InitGathererManager::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_InitGathererManager::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	AVillager* Villager = Controller->GetControlledVillager();
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_InitGathererManager::ExecuteTask IsValid(Villager) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	UGathererManager* Service = Cast<UGathererManager>(Controller->WorkManager);
	if (IsValid(Service) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_InitGathererManager::ExecuteTask IsValid(Service) == false Service not of class UGathererManager"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	Service->Init(Villager, BaseRadius, SearchClass);

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
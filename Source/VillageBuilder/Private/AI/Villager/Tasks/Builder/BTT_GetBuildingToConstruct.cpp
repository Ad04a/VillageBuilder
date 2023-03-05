// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Tasks/Builder/BTT_GetBuildingToConstruct.h"
#include "AI/Villager/Services/BTS_BuilderService.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "AI/Villager/VillagerAIController.h"


UBTT_GetBuildingToConstruct::UBTT_GetBuildingToConstruct()
{
	NodeName = TEXT("GetBuildingToConstruct");
}

EBTNodeResult::Type UBTT_GetBuildingToConstruct::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetBuildingToConstruct::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetBuildingToConstruct::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBTS_BuilderService* Service = Cast<UBTS_BuilderService>(BlackBoard->GetValueAsObject(BuilderService.SelectedKeyName));
	if (IsValid(Service) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetBuildingToConstruct::ExecuteTask IsValid(Service) == false Service not of class UBTS_BuilderService"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	Service->SetTargetBuildingCluster();

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
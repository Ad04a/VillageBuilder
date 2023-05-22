// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Tasks/Courier/BTT_GetStationToClear.h"

#include "AI/Villager/Managements/CourierManager.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "AI/Villager/VillagerAIController.h"


UBTT_GetStationToClear::UBTT_GetStationToClear()
{
	NodeName = TEXT("GetStationToClear");
}

EBTNodeResult::Type UBTT_GetStationToClear::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetStationToClear::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UCourierManager* Service = Cast<UCourierManager>(Controller->WorkManager);
	if (IsValid(Service) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetStationToClear::ExecuteTask IsValid(Service) == false Service not of class UBuilderManager"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	Service->GetStationToClear();

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
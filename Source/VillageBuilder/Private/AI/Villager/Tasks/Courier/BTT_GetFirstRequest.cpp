// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Tasks/Courier/BTT_GetFirstRequest.h"

#include "AI/Villager/Managements/CourierManager.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "AI/Villager/VillagerAIController.h"


UBTT_GetFirstRequest::UBTT_GetFirstRequest()
{
	NodeName = TEXT("GetFirstRequest");
}

EBTNodeResult::Type UBTT_GetFirstRequest::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetFirstRequest::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UCourierManager* Service = Cast<UCourierManager>(Controller->WorkManager);
	if (IsValid(Service) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetFirstRequest::ExecuteTask IsValid(Service) == false Service not of class UBuilderManager"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	Service->GetFirstRequest();

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
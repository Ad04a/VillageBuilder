// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Tasks/Builder/BTT_UpdateTargetBuildComponents.h"
#include "AI/Villager/Managements/BuilderManager.h"
#include "AI/Villager/VillagerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTT_UpdateTargetBuildComponents::UBTT_UpdateTargetBuildComponents()
{
	NodeName = TEXT("UpdateTargetBuildComponents");
}

EBTNodeResult::Type UBTT_UpdateTargetBuildComponents::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_UpdateTargetBuildComponents::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_UpdateTargetBuildComponents::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	UBuilderManager* Service = Cast<UBuilderManager>(Controller->WorkManager);
	if (IsValid(Service) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_UpdateTargetBuildComponents::ExecuteTask IsValid(Service) == false Service not of class UBuilderManager"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	Service->UpdateNeededClasses();

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GeneralTasks/BTTask_Chase.h"

UBTTask_Chase::UBTTask_Chase()
{
	NodeName = TEXT("Chase");
}

EBTNodeResult::Type UBTTask_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{

	AGeneralAIController* Controller = Cast<AGeneralAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_Chase::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_Chase::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	FVector TargetLocation = BlackBoard->GetValueAsVector(VillagerBBKeys::TargetLocation);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, TargetLocation);

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}

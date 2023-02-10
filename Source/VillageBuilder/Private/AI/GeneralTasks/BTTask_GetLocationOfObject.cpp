// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GeneralTasks/BTTask_GetLocationOfObject.h"

UBTTask_GetLocationOfObject::UBTTask_GetLocationOfObject()
{
	NodeName = TEXT("GetLocationOfObject");
}

EBTNodeResult::Type UBTTask_GetLocationOfObject::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_GetLocationOfObject::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_GetLocationOfObject::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	AActor* TargetActor = Cast<AActor>(BlackBoard->GetValueAsObject(GetSelectedBlackboardKey()));
	if (IsValid(TargetActor) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_GetLocationOfObject::ExecuteTask IsValid(TargetActor) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	BlackBoard->SetValueAsVector(WriteInto.SelectedKeyName, TargetActor->GetActorLocation());
	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
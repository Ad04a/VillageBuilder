// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/BTTask_InteractWithObject.h"

UBTTask_InteractWithObject::UBTTask_InteractWithObject()
{
	NodeName = TEXT("InteractWithObject");
}

EBTNodeResult::Type UBTTask_InteractWithObject::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_InteractWithObject::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_InteractWithObject::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UObject* TargetObject = BlackBoard->GetValueAsObject(GetSelectedBlackboardKey());
	if (IsValid(TargetObject) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_InteractWithObject::ExecuteTask IsValid(TargetObject) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	IInteractable* InteractableActor = Cast<IInteractable>(TargetObject);
	if (InteractableActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_InteractWithObject::ExecuteTask IsValid(InteractableActor) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	AVillager* Villager = Controller->GetControlledVillager();
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_InteractWithObject::ExecuteTask IsValid(Villager) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	InteractableActor->Execute_InteractRequest(TargetObject, Villager);

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
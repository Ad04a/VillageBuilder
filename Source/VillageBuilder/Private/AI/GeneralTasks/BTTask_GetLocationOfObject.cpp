// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GeneralTasks/BTTask_GetLocationOfObject.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_GetLocationOfObject::UBTTask_GetLocationOfObject()
{
	NodeName = TEXT("GetLocationOfObject");
}

EBTNodeResult::Type UBTTask_GetLocationOfObject::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_GetLocationOfObject::ExecuteTask IsValid(World) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
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
	FVector ObjectLocation = FVector();
	AActor* TargetActor = Cast<AActor>(BlackBoard->GetValueAsObject(GetSelectedBlackboardKey()));
	if (IsValid(TargetActor) == true)
	{
		ObjectLocation = TargetActor->GetActorLocation();	
	}

	USceneComponent* TargetComponent = Cast<USceneComponent>(BlackBoard->GetValueAsObject(GetSelectedBlackboardKey()));
	if (IsValid(TargetComponent) == true)
	{
		ObjectLocation = TargetComponent->GetComponentLocation();
	}

	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(World);
	if (IsValid(NavigationSystem) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_GetLocationOfObject::ExecuteTask IsValid(NavigationSystem) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	FNavLocation TargetLocation;
	if (NavigationSystem->GetRandomPointInNavigableRadius(ObjectLocation, 0, TargetLocation, nullptr) == false) {
		if (NavigationSystem->GetRandomPointInNavigableRadius(ObjectLocation, SearchRadius, TargetLocation, nullptr) == false) {
			UE_LOG(LogTemp, Error, TEXT("UBTTask_GetLocationOfObject::ExecuteTask GetRandomPointInNavigableRadius == false"));
			FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
			return EBTNodeResult::Failed;
		}
	}
	
	BlackBoard->SetValueAsVector(WriteInto.SelectedKeyName, TargetLocation.Location);
	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
	
}
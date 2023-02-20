// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GeneralTasks/BTT_RandomPointInRadius.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTT_RandomPointInRadius::UBTT_RandomPointInRadius()
{
	NodeName = TEXT("RandomPointInRadius");
}

EBTNodeResult::Type UBTT_RandomPointInRadius::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_RandomPointInRadius::ExecuteTask IsValid(World) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	AGeneralAIController* Controller = Cast<AGeneralAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_RandomPointInRadius::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_RandomPointInRadius::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	FVector ObjectLocation = BlackBoard->GetValueAsVector(GetSelectedBlackboardKey());

	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(World);
	if (IsValid(NavigationSystem) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_RandomPointInRadius::ExecuteTask IsValid(NavigationSystem) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	FNavLocation TargetLocation;
	if (NavigationSystem->GetRandomPointInNavigableRadius(ObjectLocation, SearchRadius, TargetLocation, nullptr) == false) {
		UE_LOG(LogTemp, Error, TEXT("UBTT_RandomPointInRadius::ExecuteTask GetRandomPointInNavigableRadius == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	

	BlackBoard->SetValueAsVector(WriteInto.SelectedKeyName, TargetLocation.Location);
	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}

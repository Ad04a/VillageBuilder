// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GeneralTasks/BTTask_FindLocationNearPlayer.h"


UBTTask_FindLocationNearPlayer::UBTTask_FindLocationNearPlayer() {
	NodeName = TEXT("Find Location Near Player");
}

EBTNodeResult::Type UBTTask_FindLocationNearPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) {

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_FindLocationNearPlayer::ExecuteTask IsValid(World) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_FindLocationNearPlayer::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(World, 0);
	if (IsValid(Player) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_FindLocationNearPlayer::ExecuteTask IsValid(Player) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	FVector const PlayerLocation = Player->GetActorLocation();
	FVector const SelfLocation = Controller->GetPawn()->GetActorLocation();
	if (FVector::Distance(PlayerLocation, SelfLocation) <= SearchRadius)
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	FNavLocation TargetLocation;

	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(World);
	if (IsValid(NavigationSystem) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTTask_FindLocationNearPlayer::ExecuteTask IsValid(NavigationSystem) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	if (NavigationSystem->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, TargetLocation, nullptr) == false) {
		UE_LOG(LogTemp, Error, TEXT("UBTTask_FindLocationNearPlayer::ExecuteTask GetRandomPointInNavigableRadius == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	
	Controller->GetBlackboard()->SetValueAsVector(VillagerBBKeys::TargetLocation, TargetLocation.Location);

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
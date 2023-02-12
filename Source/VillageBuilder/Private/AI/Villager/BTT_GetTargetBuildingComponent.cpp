// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/BTT_GetTargetBuildingComponent.h"
#include "GameModes/GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BaseBuildingComponent.h"


UBTT_GetTargetBuildingComponent::UBTT_GetTargetBuildingComponent()
{
	NodeName = TEXT("GetTargetBuildingComponent");
}

EBTNodeResult::Type UBTT_GetTargetBuildingComponent::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetTargetBuildingComponent::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetTargetBuildingComponent::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetTargetBuildingComponent::ExecuteTask IsValid(World) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetTargetBuildingComponent::ExecuteTask IsValid(GameMode) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	ABaseWorkStation* WorkStation = Cast<ABaseWorkStation>(BlackBoard->GetValueAsObject(WorkStationKey.SelectedKeyName));
	if (IsValid(WorkStation) == false) {
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetTargetBuildingComponent::ExecuteTask IsValid(WorkStation) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	AVillageManager* Village = GameMode->GetCurrentVillage(WorkStation);
	if (IsValid(Village) == false) {
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetTargetBuildingComponent::ExecuteTask IsValid(Village) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	WorkStation = Village->GetFirstForConstructing();
	if (IsValid(WorkStation) == false) {

		BlackBoard->ClearValue(GetSelectedBlackboardKey());
		BlackBoard->ClearValue(WriteInto.SelectedKeyName);
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	UBaseBuildingComponent* BuildComp = WorkStation->GetFirstBuildingComponent();
	if (IsValid(BuildComp) == false) {

		BlackBoard->ClearValue(GetSelectedBlackboardKey());
		BlackBoard->ClearValue(WriteInto.SelectedKeyName);
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	BlackBoard->SetValueAsObject(GetSelectedBlackboardKey(), BuildComp);
	BlackBoard->SetValueAsClass(WriteInto.SelectedKeyName, BuildComp->GetNeededClass());
	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/BTT_GetRightStorage.h"
#include "WorkSystem/BaseWorkStation.h"
#include "Components/StorageComponent.h"

UBTT_GetRightStorage::UBTT_GetRightStorage()
{
	NodeName = TEXT("GetRightStorage");
}

EBTNodeResult::Type UBTT_GetRightStorage::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	/*AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetRightStorage::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetRightStorage::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	ABaseWorkStation* WorkStation = Cast<ABaseWorkStation>(BlackBoard->GetValueAsObject(WorkStationKey.SelectedKeyName));
	if (IsValid(WorkStation) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetRightStorage::ExecuteTask IsValid(WorkStation) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	TSubclassOf<class AItem> ItemClass = BlackBoard->GetValueAsClass(SearchForClass.SelectedKeyName);
	if (IsValid(ItemClass) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetRightStorage::ExecuteTask IsValid(ItemClass) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	class UStorageComponent* StorageComponent = WorkStation->GetRightStorage(ItemClass);
	if (IsValid(StorageComponent) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GetRightStorage::ExecuteTask IsValid(StorageComponent) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	BlackBoard->SetValueAsObject(GetSelectedBlackboardKey(), StorageComponent);*/
	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}
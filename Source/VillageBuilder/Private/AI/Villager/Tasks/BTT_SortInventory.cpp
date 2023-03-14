// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Tasks/BTT_SortInventory.h"
#include "AI/Villager/Managements/WorkerManager.h"
#include "AI/Villager/VillagerAIController.h"
#include "Characters/Villager.h"
#include "Components/StorageComponent.h"
#include "Items/StoredItemInfo.h"


UBTT_SortInventory::UBTT_SortInventory()
{
	NodeName = "SortInventory";
}

EBTNodeResult::Type UBTT_SortInventory::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_EquipRightItems::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_EquipRightItems::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	UWorkerManager* WorerkService = Controller->WorkManager;
	if (IsValid(WorerkService) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_EquipRightItems::ExecuteTask IsValid(WorkService) == falses"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}


	AVillager* Villager = Controller->GetControlledVillager();
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_EquipRightItems::ExecuteTask IsValid(Villager) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	UStorageComponent* VillagerStorage = Villager->GetStorageComponent();

	TArray<TSubclassOf<AItem>> NeededClasses = WorerkService->GetNeededItemClasses();

	TSubclassOf<AItem> SelectedClass = DesiredClass;

	if (UseFirstOfNeeded == true && NeededClasses.IsEmpty() == false)
	{
		SelectedClass = NeededClasses[0];
	}

	VillagerStorage->Sort(VillagerStorage->TakeItemByClass(SelectedClass));


	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}


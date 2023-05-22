// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Tasks/BTT_GenerateItem.h"

#include "AI/Villager/VillagerAIController.h"
#include "Characters/Villager.h"
#include "WorkSystem/BaseWorkStation.h"
#include "Components/StorageComponent.h"
#include "Items/StoredItemInfo.h"
#include "Items/Item.h"

UBTT_GenerateItem::UBTT_GenerateItem()
{
	NodeName = "GenerateItem";
}

EBTNodeResult::Type UBTT_GenerateItem::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GenerateItem::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GenerateItem::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	ABaseWorkStation* WorkStationActor = Cast<ABaseWorkStation>(BlackBoard->GetValueAsObject(WorkStation.SelectedKeyName));
	if (IsValid(WorkStationActor) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GenerateItem::ExecuteTask IsValid(WorkStationActor) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	AVillager* Villager = Controller->GetControlledVillager();
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GenerateItem::ExecuteTask IsValid(Villager) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_GenerateItem::ExecuteTask IsValid(World) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	UStorageComponent* WorkStationStorage = WorkStationActor->GetStorageComponent();
	UStorageComponent* VillagerStorage = Villager->GetStorageComponent();

	for (int i = 0; i < Quntity; i++)
	{
		AItem* NewItem = AItem::SpawnItem(World, ItemToGenerate);

		if (WorkStationStorage->PlaceItem(NewItem) == true)
		{
			continue;
		}
		if (VillagerStorage->PlaceItem(NewItem) == true)
		{
			continue;
		}

		NewItem->Destroy();
	}

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
	
}
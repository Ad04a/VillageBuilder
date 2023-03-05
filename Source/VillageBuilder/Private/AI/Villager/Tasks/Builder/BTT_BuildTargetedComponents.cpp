// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Villager/Tasks/Builder/BTT_BuildTargetedComponents.h"
#include "AI/Villager/Services/BTS_BuilderService.h"
#include "AI/Villager/VillagerAIController.h"
#include "Characters/Villager.h"
#include "Components/BaseBuildingComponent.h"
#include "Components/StorageComponent.h"
#include "Items/StoredItemInfo.h"

#include "BehaviorTree/BlackboardComponent.h"


UBTT_BuildTargetedComponents::UBTT_BuildTargetedComponents()
{
	NodeName = TEXT("BuildTargetedComponents");
}

EBTNodeResult::Type UBTT_BuildTargetedComponents::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_BuildTargetedComponents::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_BuildTargetedComponents::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBTS_BuilderService* Service = Cast<UBTS_BuilderService>(BlackBoard->GetValueAsObject(BuilderService.SelectedKeyName));
	if (IsValid(Service) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_BuildTargetedComponents::ExecuteTask IsValid(Service) == false Service not of class UBTS_BuilderService"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	AVillager* Villager = Controller->GetControlledVillager();
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_BuildTargetedComponents::ExecuteTask IsValid(Villager) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	UStorageComponent* VillagerStorage = Villager->GetStorageComponent();

	TMap<UBaseBuildingComponent*, TSubclassOf<AItem>> TargetBuildComponents = Service->UpdateNeededClasses();
	TArray<TSubclassOf<AItem >> NeededClasses = Service->GetNededItemClasses();

	for (TPair<UStoredItemInfo*, FIntPoint> Item : VillagerStorage->GetAllItems())
	{
		TSubclassOf<AItem> ItemClass = Item.Key->GetItemInfo().ItemClass;
		if (NeededClasses.Contains(ItemClass) == false)
		{
			continue;
		}
		UBaseBuildingComponent* BuildComponent = *TargetBuildComponents.FindKey(ItemClass);
		if (IsValid(BuildComponent) == false)
		{
			continue;
		}
		UStoredItemInfo* ItemInfo = VillagerStorage->TakeItemByClass(ItemClass);
		VillagerStorage->Sort(ItemInfo);

		IInteractable* InteractableObject = Cast<IInteractable>(BuildComponent);
		if (InteractableObject == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("UBTT_BuildTargetedComponents::ExecuteTask IsValid(InteractableActor) == false"));
			continue;
		}
		InteractableObject->Execute_InteractRequest(BuildComponent, Villager);

		TargetBuildComponents = Service->UpdateNeededClasses();
		NeededClasses = Service->GetNededItemClasses();
	}

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Decorators/BTD_AtleastOneRightEquiped.h"
#include "AI/Villager/Services/BTS_WorkerService.h"
#include "AI/Villager/VillagerAIController.h"
#include "Characters/Villager.h"
#include "WorkSystem/BaseWorkStation.h"
#include "Components/StorageComponent.h"
#include "Items/StoredItemInfo.h"

UBTD_AtleastOneRightEquiped::UBTD_AtleastOneRightEquiped()
{
	NodeName = "AtleastOneRightEquiped";
}

bool UBTD_AtleastOneRightEquiped::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) const
{
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComponent, NodeMemory);
	if (bSuccess == false)
	{
		return false;
	}
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_EquipRightItems::ExecuteTask IsValid(Controller) == false"));
		return false;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_EquipRightItems::ExecuteTask IsValid(BlackBoard) == false"));
		return false;
	}

	UBTS_WorkerService* WorerkService = Cast<UBTS_WorkerService>(BlackBoard->GetValueAsObject(WorkService.SelectedKeyName));
	if (IsValid(WorerkService) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_EquipRightItems::ExecuteTask IsValid(WorkService) == false"));
		return false;
	}

	AVillager* Villager = Controller->GetControlledVillager();
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_EquipRightItems::ExecuteTask IsValid(Villager) == false"));
		return false;
	}
	UStorageComponent* VillagerStorage = Villager->GetStorageComponent();
	TArray<TSubclassOf<AItem >> NeededClasses = WorerkService->GetNededItemClasses();

	for (TSubclassOf<AItem > ItemClass : NeededClasses)
	{
		UStoredItemInfo* Item = VillagerStorage->TakeItemByClass(ItemClass);
		if (IsValid(Item) == false)
		{
			continue;
		}
		VillagerStorage->TryPlaceItem(Item);
		return true;
	}

	return false;
}
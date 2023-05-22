// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Managements/WorkerManager.h"
#include "WorkSystem/VillageManager.h"
#include "Characters/Villager.h"
#include "WorkSystem/BaseWorkStation.h"
#include "Components/StorageComponent.h"
#include "Items/StoredItemInfo.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UWorkerManager* UWorkerManager::CreateInstance(UObject* Outer, TSubclassOf<UWorkerManager> ManagerClass, AVillageManager* InVillage, UBlackboardComponent* InBlackboard, TArray<struct FBlackboardKeySelector> InKeys, AVillager* InVillager)
{
	if (IsValid(Outer) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_WorkerService::OnBecomeRelevant No Outer object Specified or is invalid"));
		return nullptr;
	}

	if (IsValid(ManagerClass) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTS_WorkerService::OnBecomeRelevant No Class Specified"));
		return nullptr;
	}

	UWorkerManager* WorkerManager = NewObject<UWorkerManager>(Outer, ManagerClass);
	if (IsValid(WorkerManager) == false) {
		UE_LOG(LogTemp, Error, TEXT("UBTS_WorkerService::OnBecomeRelevant IsValid(WorkerManager) == false"));
		return nullptr;
	}

	WorkerManager->Village = InVillage;
	WorkerManager->BlackBoard = InBlackboard;
	WorkerManager->GivenKeys = InKeys;
	WorkerManager->WorkStation = InVillage->GetWorkPlaceFor(InVillager->ID);
	WorkerManager->Villager = InVillager;

	if (WorkerManager->CheckGivenKeys() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_WorkerService::OnBecomeRelevant Passed Blackboard Keys are not valid for the given WorkManager of class %s"), *WorkerManager->GetClass()->GetName());
		return nullptr;
	}

	WorkerManager->CanTick = true;

	return WorkerManager;
}

void UWorkerManager::Tick(float DeltaTime)
{
	if (CanTick == false)
	{
		return;
	}
	UStorageComponent* VillagerStorage = Villager->GetStorageComponent();

	TMap<UStoredItemInfo*, FIntPoint> AllItems = VillagerStorage->GetAllItems();
	if (IsValid(WorkStation) == true)
	{
		UStorageComponent* WorkStationStorage = WorkStation->GetStorageComponent();
		AllItems.Append(WorkStationStorage->GetAllItems());
	}
	TArray<TSubclassOf<AItem>>NeededClasses = GetNeededItemClasses();
	TArray<TSubclassOf<AItem>> MissingClasses;
	for (TPair<UStoredItemInfo*, FIntPoint> Item : AllItems)
	{
		if (IsValid(Item.Key) == false)
		{
			continue;
		}
		int Index = NeededClasses.Find(Item.Key->GetItemInfo().ItemClass);
		if (NeededClasses.IsValidIndex(Index) == false)
		{
			continue;
		}
		NeededClasses.RemoveAt(Index);
	}

	CommitRequest(NeededClasses);
}

void UWorkerManager::CommitRequest(TArray<TSubclassOf<AItem>> Classes, bool IsFull)
{
	Village->CommitRequest(Classes, Villager, IsFull);
}


TStatId UWorkerManager::GetStatId() const
{
	return TStatId();
}

void UWorkerManager::Clear(AVillager* InVillager)
{ 
	if (IsValid(InVillager) == true)
	{
		InVillager->OnDeath.RemoveAll(this);
	}
	CanTick = false; 
	Villager = nullptr; 
	Village = nullptr;  
	BlackBoard = nullptr; 
	ConditionalBeginDestroy(); 
}
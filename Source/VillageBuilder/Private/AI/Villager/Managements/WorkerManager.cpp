// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Managements/WorkerManager.h"
#include "WorkSystem/VillageManager.h"
#include "BehaviorTree/BlackboardComponent.h"

UWorkerManager* UWorkerManager::CreateInstance(UObject* Outer, TSubclassOf<UWorkerManager> ManagerClass, AVillageManager* InVillage, UBlackboardComponent* InBlackboard, TArray<struct FBlackboardKeySelector> InKeys)
{
	if (IsValid(Outer) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_WorkerService::OnBecomeRelevant No Outer object Specified or is invalid"));
		return nullptr;
	}

	if (IsValid(ManagerClass) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_WorkerService::OnBecomeRelevant No Class Specified"));
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

	if (WorkerManager->CheckGivenKeys() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_WorkerService::OnBecomeRelevant Passed Blackboard Keys are not valid for the given WorkManager of class %s"), *WorkerManager->GetClass()->GetName());
		return nullptr;
	}

	return WorkerManager;
}
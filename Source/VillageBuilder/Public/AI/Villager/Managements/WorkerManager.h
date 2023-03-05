// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorkerManager.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UWorkerManager : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<class AItem>> NededItemClasses;

	UPROPERTY(VisibleAnywhere)
	TArray<struct FBlackboardKeySelector> GivenKeys;

	class AVillageManager* Village;
	class UBlackboardComponent* BlackBoard;

public:
	static UWorkerManager* CreateInstance(UObject* Outer, TSubclassOf< UWorkerManager> ManagerClass, class AVillageManager* InVillage, class UBlackboardComponent* InBlackboard, TArray<struct FBlackboardKeySelector> InKeys);
	virtual bool CheckGivenKeys() { return true; }
	void SetNededItemClasses(TArray<TSubclassOf<class AItem>> Classes = TArray<TSubclassOf<class AItem>>()) { NededItemClasses = Classes; }
	TArray<TSubclassOf<class AItem>> GetNeededItemClasses() { return NededItemClasses; }
};

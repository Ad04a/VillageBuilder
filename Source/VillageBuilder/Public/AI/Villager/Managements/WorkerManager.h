#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BehaviorTree/BehaviorTreeTypes.h"
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
	TArray<FBlackboardKeySelector> GivenKeys;

	class AVillageManager* Village;
	class UBlackboardComponent* BlackBoard;

public:
	static UWorkerManager* CreateInstance(UObject* Outer, TSubclassOf< UWorkerManager> ManagerClass, class AVillageManager* InVillage, class UBlackboardComponent* InBlackboard, TArray<struct FBlackboardKeySelector> InKeys);
	virtual bool CheckGivenKeys() { return true; }
	void SetNededItemClasses(TArray<TSubclassOf<class AItem>> Classes = TArray<TSubclassOf<class AItem>>()) { NededItemClasses.Empty(); NededItemClasses = Classes; }
	TArray<TSubclassOf<class AItem>> GetNeededItemClasses() { return NededItemClasses; }
	virtual void Clear() { Village = nullptr;  BlackBoard = nullptr; ConditionalBeginDestroy(); }
};
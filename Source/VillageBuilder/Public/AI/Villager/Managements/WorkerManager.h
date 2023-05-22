#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BehaviorTree/BehaviorTreeTypes.h"
#include "WorkerManager.generated.h"

/**
 *
 */
UCLASS()
class VILLAGEBUILDER_API UWorkerManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<class AItem>> NededItemClasses;

	UPROPERTY(VisibleAnywhere)
	class AVillager* Villager;

	UPROPERTY(VisibleAnywhere)
	class ABaseWorkStation* WorkStation;

	UPROPERTY(VisibleAnywhere)
	TArray<FBlackboardKeySelector> GivenKeys;

	class AVillageManager* Village;
	class UBlackboardComponent* BlackBoard;

	bool CanTick = false;

public:
	virtual void Tick(float DeltaTime) override;
	TStatId GetStatId() const override;
	static UWorkerManager* CreateInstance(UObject* Outer, TSubclassOf<UWorkerManager> ManagerClass, AVillageManager* InVillage, UBlackboardComponent* InBlackboard, TArray<struct FBlackboardKeySelector> InKeys, AVillager* InVillager);
	virtual bool CheckGivenKeys() { return true; }
	void SetNededItemClasses(TArray<TSubclassOf<class AItem>> Classes = TArray<TSubclassOf<class AItem>>()) { NededItemClasses.Empty(); NededItemClasses = Classes; }
	TArray<TSubclassOf<class AItem>> GetNeededItemClasses() { return NededItemClasses; }
	UFUNCTION()
	virtual void Clear(AVillager* InVillager);
	void CommitRequest(TArray<TSubclassOf<class AItem>> Classes, bool IsFull = false);
};
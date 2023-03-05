// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_WorkerService.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTS_WorkerService : public UBTService
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector WorkStation;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	TArray<struct FBlackboardKeySelector> KeysToPassToManager;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UWorkerManager> ManagerClass;

public:
	UBTS_WorkerService();

	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

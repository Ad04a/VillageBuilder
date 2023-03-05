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
	struct FBlackboardKeySelector WorkService;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector WorkStation;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector HasWorkCheck;

	class AVillageManager* Village;
	class UBlackboardComponent* BlackBoard;

	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<class AItem>> NededItemClasses;

public:
	UBTS_WorkerService();

	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;

	TArray<TSubclassOf<class AItem>> GetNededItemClasses() { return NededItemClasses; }
};

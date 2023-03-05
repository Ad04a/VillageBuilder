// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Villager/Services/BTS_WorkerService.h"
#include "BTS_BuilderService.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTS_BuilderService : public UBTS_WorkerService
{
	GENERATED_BODY()

public:
	UBTS_BuilderService();
protected:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector TargetWorkStation;

	UPROPERTY()
	class UBuildingClusterComponent* TargetBuildingCluster;

	UFUNCTION()
	void ResetBuildingCluster(bool State);

public:
	void SetTargetBuildingCluster();
	TMap<class UBaseBuildingComponent*, TSubclassOf<class AItem>> UpdateNeededClasses();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

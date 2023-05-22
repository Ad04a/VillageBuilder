// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Villager/Managements/WorkerManager.h"
#include "BuilderManager.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBuilderManager : public UWorkerManager
{
	GENERATED_BODY()
protected:

	class UBuildingClusterComponent* TargetBuildingCluster;

	UFUNCTION()
	void ResetBuildingCluster(bool State);

public:

	virtual bool CheckGivenKeys() override;
	virtual void Clear(AVillager* InVillager) override;

	void SetTargetBuildingCluster();
	TMap<class UBaseBuildingComponent*, TSubclassOf<class AItem>> UpdateNeededClasses();
};

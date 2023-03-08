// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Villager/Managements/WorkerManager.h"
#include "GathererManager.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UGathererManager : public UWorkerManager, public FTickableGameObject
{
	GENERATED_BODY()
protected:

	class AVillager* Gatherer;

	float Radius = 0;

	TArray<AActor*> RememberedItems;

	TSubclassOf<class AItem> TargetClass;

public:

	void Tick(float DeltaTime) override;
	TStatId GetStatId() const override;

	virtual bool CheckGivenKeys() override;
	virtual void Clear() override;

	void Init(class AVillager* InGatherer, float BaseRadius, TSubclassOf<class AItem> SearchClass);


};

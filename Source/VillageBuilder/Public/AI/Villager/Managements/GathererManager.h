// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Villager/Managements/WorkerManager.h"
#include "GathererManager.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UGathererManager : public UWorkerManager
{
	GENERATED_BODY()
protected:

	class AVillager* Gatherer;

	float Radius = 0;

	UPROPERTY()
	TArray<AActor*> RememberedItems;

	TSubclassOf<class AItem> TargetClass;

public:

	void Tick(float DeltaTime) override;

	virtual bool CheckGivenKeys() override;
	virtual void Clear(AVillager* InVillager) override;

	void Init(class AVillager* InGatherer, float BaseRadius, TSubclassOf<class AItem> SearchClass);


};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Villager/Managements/WorkerManager.h"
#include "CourierManager.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UCourierManager : public UWorkerManager
{
	GENERATED_BODY()
	
public:
	virtual bool CheckGivenKeys() override;
	virtual void Clear(AVillager* InVillager) override;
	void Tick(float DeltaTime) override;
	void GetFirstRequest();
	void GetStationToClear();
};

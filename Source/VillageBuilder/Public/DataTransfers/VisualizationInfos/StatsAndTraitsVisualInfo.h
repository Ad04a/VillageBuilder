// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTransfers/VisualizationInfo.h"
#include "Headers/LoadInfo.h"
#include "StatsAndTraitsVisualInfo.generated.h"

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FInitiatorStatUpdatedSignature, EStat, StatName, float, Current, float, Max);

UCLASS()
class VILLAGEBUILDER_API UStatsAndTraitsVisualInfo : public UVisualizationInfo
{
	GENERATED_BODY()
protected:
	UFUNCTION()
	void PassStatUpdate(EStat StatName, float Current, float Max);

	class AVillager* LinkedVillager;

public:
	static UVisualizationInfo* CreateVisualInfo(AActor* InActor);
	virtual void Clear() override;

	FInitiatorStatUpdatedSignature OnStatUpdated;

	FVillagerVisualInfoStruct VisualStruct;
	void NotifyLinked();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTransfers/VisualizationInfo.h"
#include "Headers/StatAndTraitEnums.h"
#include "StatsAndTraitsVisualInfo.generated.h"

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FInitiatorStatUpdatedSignature, EStat, StatName, int, Current, int, Max);

UCLASS()
class VILLAGEBUILDER_API UStatsAndTraitsVisualInfo : public UVisualizationInfo
{
	GENERATED_BODY()
public:
	static UVisualizationInfo* CreateVisualInfo(AActor* InActor);

	FInitiatorStatUpdatedSignature OnStatUpdated;

	FString Name;
	TMap<TEnumAsByte<ETrait>, float> TraitMap;
	TMap<TEnumAsByte<ETrait>, float> Scaling;
};

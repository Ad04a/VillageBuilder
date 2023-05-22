// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTransfers/VisualizationInfo.h"
#include "SpectatorVisualInfo.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API USpectatorVisualInfo : public UVisualizationInfo
{
	GENERATED_BODY()
protected:
	class AGameplayModeBase* GameMode;

	float TimeSurvived = 0;
public:
	UFUNCTION()
	void DeleteSave();

	float GetTimeSurvived() { return TimeSurvived; }

	static UVisualizationInfo* CreateVisualInfo(AActor* InActor);
	virtual void Clear() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTransfers/VisualizationInfo.h"
#include "OptionsVisualInfo.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UOptionsVisualInfo : public UVisualizationInfo
{
	GENERATED_BODY()

protected:
	class AGameplayModeBase* GameMode;
public:
	UFUNCTION()
	void ExitGame();
	static UVisualizationInfo* CreateVisualInfo(AActor* InActor);
	virtual void Clear() override;
};
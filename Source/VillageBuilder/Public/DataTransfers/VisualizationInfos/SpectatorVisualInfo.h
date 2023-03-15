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

public:
	UFUNCTION()
	void DeleteSave();

	UFUNCTION()
	void Spectate();

	static UVisualizationInfo* CreateVisualInfo(AActor* InActor);
	virtual void Clear() override;
};

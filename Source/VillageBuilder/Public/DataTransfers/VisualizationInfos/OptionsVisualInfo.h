// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTransfers/VisualizationInfo.h"
#include "Headers/OptionStructures.h"
#include "OptionsVisualInfo.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FGraphicsSaved, FGraphicsSettings, Settings);
UCLASS()
class VILLAGEBUILDER_API UOptionsVisualInfo : public UVisualizationInfo
{
	GENERATED_BODY()

protected:
	class AGameplayModeBase* GameMode;
	class UGameUserSettings* GameSettings;
public:
	FGraphicsSaved OnGraphicsSaved;

	UFUNCTION()
	void ExitGame();

	UFUNCTION()
	void RecieveUpdatedGraphics(FGraphicsSettings Settings);

	static UVisualizationInfo* CreateVisualInfo(AActor* InActor);
	virtual void Clear() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/OptionStructures.h"
#include "GraphicsQualityWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FGraphicsUpdatedSignature, FGraphicsSettings, Settings);

UCLASS()class VILLAGEBUILDER_API UGraphicsQualityWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class USlider* OverallScalabilityLevel;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class USlider* AntiAliasingQuality;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class USlider* FoliageQuality;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class USlider* PostProcessingQuality;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class USlider* ShadingQuality;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class USlider* ShadowQuality;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class USlider* TextureQuality;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class USlider* ViewDistanceQuality;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class USlider* VisualEffectQuality;

	UFUNCTION()
	void OnUpdate(float Value);

	bool bCanUpdate = true;

public:

	FGraphicsUpdatedSignature OnGraphicsUpdated;
	FGraphicsUpdatedSignature   RequestUpdate;

	void UpdateWindowMode(EWindowMode::Type InWindowMode);
	UFUNCTION()
	void UpdateScaleability(FGraphicsSettings Settings);
	void UpdateVSync(bool State);
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
};

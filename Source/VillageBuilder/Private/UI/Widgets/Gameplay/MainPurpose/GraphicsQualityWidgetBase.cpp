// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Gameplay/MainPurpose/GraphicsQualityWidgetBase.h"

#include "Components/Slider.h"

void UGraphicsQualityWidgetBase::NativeOnInitialized()
{
	TArray<USlider*> Sliders;
	Sliders.Add(AntiAliasingQuality);
	Sliders.Add(FoliageQuality);
	Sliders.Add(PostProcessingQuality);
	Sliders.Add(ShadingQuality);
	Sliders.Add(ShadowQuality);
	Sliders.Add(TextureQuality);
	Sliders.Add(ViewDistanceQuality);
	Sliders.Add(VisualEffectQuality);

	for (USlider* Slider : Sliders)
	{
		Slider->SetMinValue(-0.5);
		Slider->SetMaxValue(3.5);
		Slider->SetStepSize(1);
		Slider->MouseUsesStep = true;
		Slider->OnValueChanged.AddDynamic(this, &UGraphicsQualityWidgetBase::OnUpdate);
	}
	OverallScalabilityLevel->SetMinValue(-1.5);
	OverallScalabilityLevel->SetMaxValue(3.5);
	OverallScalabilityLevel->SetStepSize(1);
	OverallScalabilityLevel->MouseUsesStep = true;
	OverallScalabilityLevel->OnValueChanged.AddDynamic(this, &UGraphicsQualityWidgetBase::OnQualityUpdate);
}

void UGraphicsQualityWidgetBase::OnUpdate(float Value)
{
	if (bCanUpdate == false)
	{
		return;
	}

	if (Value != int(Value))
	{
		return;
	}

	FGraphicsSettings NewSettings;
	NewSettings.AntiAliasingQuality     = AntiAliasingQuality->GetValue();
	NewSettings.FoliageQuality			= FoliageQuality->GetValue();
	NewSettings.PostProcessingQuality	= PostProcessingQuality->GetValue();
	NewSettings.ShadingQuality			= ShadingQuality->GetValue();
	NewSettings.ShadowQuality			= ShadowQuality->GetValue();
	NewSettings.TextureQuality			= TextureQuality->GetValue();
	NewSettings.ViewDistanceQuality		= ViewDistanceQuality->GetValue();
	NewSettings.VisualEffectQuality		= VisualEffectQuality->GetValue();

	OnGraphicsUpdated.ExecuteIfBound(NewSettings);
}

void UGraphicsQualityWidgetBase::OnQualityUpdate(float Value)
{
	OnQualityUpdated.ExecuteIfBound(Value);
}

void UGraphicsQualityWidgetBase::UpdateWindowMode(EWindowMode::Type InWindowMode)
{

}

void UGraphicsQualityWidgetBase::UpdateScaleability(FGraphicsSettings Settings)
{
	bCanUpdate = false;
	OverallScalabilityLevel->SetValue(Settings.OverallScalabilityLevel);
	AntiAliasingQuality->SetValue(Settings.AntiAliasingQuality);
	FoliageQuality->SetValue(Settings.FoliageQuality);
	PostProcessingQuality->SetValue(Settings.PostProcessingQuality);
	ShadingQuality->SetValue(Settings.ShadingQuality);
	ShadowQuality->SetValue(Settings.ShadowQuality);
	TextureQuality->SetValue(Settings.TextureQuality);
	ViewDistanceQuality->SetValue(Settings.ViewDistanceQuality);
	VisualEffectQuality->SetValue(Settings.VisualEffectQuality);
	bCanUpdate = true;
}

void UGraphicsQualityWidgetBase::UpdateVSync(bool State)
{

}

void UGraphicsQualityWidgetBase::NativeConstruct()
{
	FGraphicsSettings NewSettings = FGraphicsSettings();
	NewSettings.bIsTestSignal = true;
	RequestUpdate.ExecuteIfBound(NewSettings);
}
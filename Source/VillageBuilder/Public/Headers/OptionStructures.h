#pragma once

#include "OptionStructures.generated.h"

USTRUCT(BlueprintType)
struct FGraphicsSettings
{
	GENERATED_BODY()

	bool bIsTestSignal = false;

	EWindowMode::Type FullscreenMode;

	int OverallScalabilityLevel = -1;
	int AntiAliasingQuality;
	int FoliageQuality;
	int PostProcessingQuality;
	int ShadingQuality;
	int ShadowQuality;
	int TextureQuality;
	int ViewDistanceQuality;
	int VisualEffectQuality;

	bool VSyncEnabled;

};

USTRUCT(BlueprintType)
struct FSoundSettings
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FControlsSettings
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FSettingsStruct
{
	GENERATED_BODY()
	FGraphicsSettings GraphicsSettings;
	FSoundSettings    SoundSettings;
	FControlsSettings ControlsSettings;
};
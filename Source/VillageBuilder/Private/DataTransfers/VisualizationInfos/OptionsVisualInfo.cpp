// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/OptionsVisualInfo.h"
#include "GameModes/GameplayModeBase.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

UVisualizationInfo* UOptionsVisualInfo::CreateVisualInfo(AActor* InActor)
{
	UOptionsVisualInfo* Info = NewObject<UOptionsVisualInfo>();
	if (IsValid(Info) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UOptionsVisualInfo::CreateVisualInfo Cannot create info"));
		return nullptr;
	}
	UWorld* World = InActor->GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UOptionsVisualInfo::CreateVisualInfo IsValid(World) == false"));
		return nullptr;
	}

	Info->GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(Info->GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("UOptionsVisualInfo::CreateVisualInfo IsValid(GameMode) == false"));
		return nullptr;
	}

	Info->GameSettings = GEngine->GameUserSettings;
	if (IsValid(Info->GameSettings) == false) {
		UE_LOG(LogTemp, Error, TEXT("UOptionsVisualInfo::CreateVisualInfo IsValid(GameSettings) == false"));
		return nullptr;
	}

	return Info;
}

void UOptionsVisualInfo::RecieveUpdatedGraphics(FGraphicsSettings Settings)
{
	if (Settings.bIsTestSignal == false)
	{
		GameSettings->SetOverallScalabilityLevel(Settings.OverallScalabilityLevel);

		GameSettings->SetAntiAliasingQuality(Settings.AntiAliasingQuality);
		GameSettings->SetFoliageQuality(Settings.FoliageQuality);
		GameSettings->SetPostProcessingQuality(Settings.PostProcessingQuality);
		GameSettings->SetShadingQuality(Settings.ShadingQuality);
		GameSettings->SetShadowQuality(Settings.ShadowQuality);
		GameSettings->SetTextureQuality(Settings.TextureQuality);
		GameSettings->SetViewDistanceQuality(Settings.ViewDistanceQuality);
		GameSettings->SetVisualEffectQuality(Settings.VisualEffectQuality);
	}

	GameSettings->ApplySettings(false);

	FGraphicsSettings NewSettings;

	NewSettings.OverallScalabilityLevel = GameSettings->GetOverallScalabilityLevel();
	NewSettings.AntiAliasingQuality     = GameSettings->GetAntiAliasingQuality();
	NewSettings.FoliageQuality          = GameSettings->GetFoliageQuality();
	NewSettings.PostProcessingQuality   = GameSettings->GetPostProcessingQuality();
	NewSettings.ShadingQuality			= GameSettings->GetShadingQuality();
	NewSettings.ShadowQuality			= GameSettings->GetShadowQuality();
	NewSettings.TextureQuality			= GameSettings->GetTextureQuality();
	NewSettings.ViewDistanceQuality		= GameSettings->GetViewDistanceQuality();
	NewSettings.VisualEffectQuality		= GameSettings->GetVisualEffectQuality();


	OnGraphicsSaved.ExecuteIfBound(NewSettings);

}

void UOptionsVisualInfo::ExitGame()
{
	GameMode->EndGame();
}

void UOptionsVisualInfo::Clear()
{
	Super::Clear();
	GameMode = nullptr;
	GameSettings = nullptr;
}
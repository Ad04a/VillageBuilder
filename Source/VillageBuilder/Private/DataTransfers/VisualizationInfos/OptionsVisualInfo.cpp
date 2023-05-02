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
	ReturnUpdate();
}

void UOptionsVisualInfo::RecieveUpdatedQuality(int Value)
{
	UpdateAll(Value);
	GameSettings->ApplySettings(false);
	ReturnUpdate();
}

void UOptionsVisualInfo::ReturnUpdate()
{
	FGraphicsSettings NewSettings;

	NewSettings.OverallScalabilityLevel = GetCurrentOverallLevel();
	NewSettings.AntiAliasingQuality = GameSettings->GetAntiAliasingQuality();
	NewSettings.FoliageQuality = GameSettings->GetFoliageQuality();
	NewSettings.PostProcessingQuality = GameSettings->GetPostProcessingQuality();
	NewSettings.ShadingQuality = GameSettings->GetShadingQuality();
	NewSettings.ShadowQuality = GameSettings->GetShadowQuality();
	NewSettings.TextureQuality = GameSettings->GetTextureQuality();
	NewSettings.ViewDistanceQuality = GameSettings->GetViewDistanceQuality();
	NewSettings.VisualEffectQuality = GameSettings->GetVisualEffectQuality();


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

void UOptionsVisualInfo::UpdateAll(int Value)
{
	GameSettings->SetAntiAliasingQuality(Value);
	GameSettings->SetFoliageQuality(Value);
	GameSettings->SetPostProcessingQuality(Value);
	GameSettings->SetShadingQuality(Value);
	GameSettings->SetShadowQuality(Value);
	GameSettings->SetTextureQuality(Value);
	GameSettings->SetViewDistanceQuality(Value);
	GameSettings->SetVisualEffectQuality(Value);
}

int UOptionsVisualInfo::GetCurrentOverallLevel()
{
	TArray<int> Settings;
	Settings.Add(GameSettings->GetFoliageQuality());
	Settings.Add(GameSettings->GetPostProcessingQuality());
	Settings.Add(GameSettings->GetShadingQuality());
	Settings.Add(GameSettings->GetShadowQuality());
	Settings.Add(GameSettings->GetTextureQuality());
	Settings.Add(GameSettings->GetViewDistanceQuality());
	Settings.Add(GameSettings->GetVisualEffectQuality());

	int Overall = GameSettings->GetAntiAliasingQuality();

	for (int Value : Settings)
	{
		if (Overall != Value)
		{
			return -1;
		}
		Overall = Value;
	}
	return Overall;
}
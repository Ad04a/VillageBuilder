// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/SpectatorVisualInfo.h"
#include "GameModes/GameplayModeBase.h"
#include "VillageBuilderPlayerController.h"

#include "Kismet/GameplayStatics.h"

UVisualizationInfo* USpectatorVisualInfo::CreateVisualInfo(AActor* InActor)
{
	USpectatorVisualInfo* Info = NewObject<USpectatorVisualInfo>();
	if (IsValid(Info) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("USpectatorVisualInfo::CreateVisualInfo Cannot create info"));
		return nullptr;
	}
	UWorld* World = InActor->GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("USpectatorVisualInfo::CreateVisualInfo IsValid(World) == false"));
		return nullptr;
	}

	Info->GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(Info->GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("USpectatorVisualInfo::CreateVisualInfo IsValid(GameMode) == false"));
		return nullptr;
	}

	Info->TimeSurvived = Info->GameMode->GetPlayerController(0)->GetCurrentSurvivedTime();

	return Info;
}

void USpectatorVisualInfo::DeleteSave()
{
	GameMode->DeleteSave();
}

void USpectatorVisualInfo::Clear()
{
	Super::Clear();
	GameMode = nullptr;
}
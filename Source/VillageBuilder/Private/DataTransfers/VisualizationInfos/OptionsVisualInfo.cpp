// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/OptionsVisualInfo.h"
#include "GameMOdes/GameplayModeBase.h"

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
	return Info;
}

void UOptionsVisualInfo::ExitGame()
{
	GameMode->EndGame();
}

void UOptionsVisualInfo::Clear()
{
	GameMode = nullptr;
}
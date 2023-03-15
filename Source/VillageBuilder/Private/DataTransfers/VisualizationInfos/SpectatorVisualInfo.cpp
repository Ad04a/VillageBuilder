// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/SpectatorVisualInfo.h"
#include "GameMOdes/GameplayModeBase.h"

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
	return Info;
}

void USpectatorVisualInfo::DeleteSave()
{
	GameMode->DeleteSave();
}
void USpectatorVisualInfo::Spectate()
{

}

void USpectatorVisualInfo::Clear()
{
	Super::Clear();
	GameMode = nullptr;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/BuildingVisualInfo.h"
#include "GameMOdes/GameplayModeBase.h"

#include "Kismet/GameplayStatics.h"

UVisualizationInfo* UBuildingVisualInfo::CreateVisualInfo(AActor* InActor)
{
	UBuildingVisualInfo* Info = NewObject<UBuildingVisualInfo>();
	if (IsValid(Info) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBuildingVisualInfo::CreateVisualInfo Cannot create info"));
		return nullptr;
	}
	UWorld* World = InActor->GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBuildingVisualInfo::CreateVisualInfo IsValid(World) == false"));
		return nullptr;
	}

	Info->GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(Info->GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("UBuildingVisualInfo::CreateVisualInfo IsValid(GameMode) == false"));
		return nullptr;
	}
	return Info;
}

TArray<FString> UBuildingVisualInfo::GetBuildingNames()
{
	return GameMode->GetAllBuildingNames();
}

bool UBuildingVisualInfo::BuildingSelected(FString BuildingName)
{
	return GameMode->GivePlayerBuildItem(BuildingName);
}

void UBuildingVisualInfo::Clear()
{
	GameMode = nullptr;
}
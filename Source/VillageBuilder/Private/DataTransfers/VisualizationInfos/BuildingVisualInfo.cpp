// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/BuildingVisualInfo.h"
#include "Items/BuilderItem.h"
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
	
	ABuilderItem* Item = Cast<ABuilderItem>(InActor);
	if (IsValid(Item) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBuildingVisualInfo::CreateVisualInfo Cannot create info IsValid(Item) == false"));
		return nullptr;
	}

	Info->Item = Item;

	return Info;
}

TArray<FString> UBuildingVisualInfo::GetBuildingNames()
{
	UWorld* World = Item->GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBuildingVisualInfo::CreateVisualInfo IsValid(World) == false"));
		return TArray<FString>();
	}

	AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("UBuildingVisualInfo::CreateVisualInfo IsValid(GameMode) == false"));
		return TArray<FString>();
	}
	BuildingsInfo = GameMode->GetBuildingsInfo();
	return GameMode->GetAllBuildingNames();
}

void UBuildingVisualInfo::BuildingSelected(FString BuildingName)
{
	if (BuildingsInfo.Contains(BuildingName) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBuildingVisualInfo::BuildingSelected BuildingsInfo.Contains(BuildingName) == false"));
		return;
	}
	Item->BindProjectionToPlayer(*BuildingsInfo.Find(BuildingName));
}

void UBuildingVisualInfo::Clear()
{
	Super::Clear();
	Item = nullptr;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/InviteVisualInfo.h"
#include "GameModes/GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"

UVisualizationInfo* UInviteVisualInfo::CreateVisualInfo(AActor* InActor)
{
	UInviteVisualInfo* Info = NewObject<UInviteVisualInfo>();
	if (IsValid(Info) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UInviteVisualInfo::CreateVisualInfo Cannot create info"));
		return nullptr;
	}

	Info->Villager = Cast<AVillager>(InActor);
	if (IsValid(Info->Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UInviteVisualInfo::CreateVisualInfo Give entity is not of class AVillager"));
		return nullptr;
	}

	return Info;
}

void UInviteVisualInfo::SetInviter(class AVillageMayor* InInviter)
{

	UWorld* World = InInviter->GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UInviteVisualInfo::SetInviter IsValid(World) == false"));
		return;
	}

	AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("UInviteVisualInfo::SetInviter IsValid(GameMode) == false"));
		return;
	}

	Village = GameMode->GetCurrentVillage(InInviter);
}


void UInviteVisualInfo::InviteVillager()
{
	Village->AddVillagerToColony(Villager);
}

void UInviteVisualInfo::Clear()
{
	Super::Clear();
	Village  = nullptr;
	Villager = nullptr;
}
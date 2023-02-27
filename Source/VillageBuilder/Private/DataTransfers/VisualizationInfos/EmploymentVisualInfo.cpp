// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/EmploymentVisualInfo.h"
#include "GameMOdes/GameplayModeBase.h"
#include "WorkSystem/BaseWorkStation.h"

#include "Kismet/GameplayStatics.h"


UVisualizationInfo* UEmploymentVisualInfo::CreateVisualInfo(AActor* InActor)
{
	UEmploymentVisualInfo* Info = NewObject<UEmploymentVisualInfo>();
	if (IsValid(Info) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UEmploymentVisualInfo::CreateVisualInfo Cannot create info"));
		return nullptr;
	}

	Info->WorkStation = Cast<ABaseWorkStation>(InActor);
	if (IsValid(Info->WorkStation) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UEmploymentVisualInfo::CreateVisualInfo Cannot create info: Given Actor is not ABaseWorkStation"));
		return nullptr;
	}

	UWorld* World = InActor->GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UEmploymentVisualInfo::CreateVisualInfo IsValid(World) == false"));
		return nullptr;
	}

	AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("UEmploymentVisualInfo::CreateVisualInfo IsValid(GameMode) == false"));
		return nullptr;
	}
	Info->Village = GameMode->GetCurrentVillage(Info->WorkStation);
	Info->Village->OnVillagersUpdated.BindDynamic(Info, &UEmploymentVisualInfo::RecieveUpdatedVillagers);
	return Info;
}

void UEmploymentVisualInfo::RecieveUpdatedVillagers(TArray<AVillager*> Villagers)
{
	TArray<FVillagerVisualInfoStruct> VisualStructs;
	for (AVillager* Villager : Villagers)
	{
		VisualStructs.Add(Villager->ExtractVisualInfo());
	}
	FStationStruct StationStruct;
	StationStruct.ScalingMap = WorkStation->GetModifiers();
	StationStruct.HiredID = -1;
	StationStruct.StationName = WorkStation->GetName();
	if (Villagers.Contains(Village->GetWorkerAt(WorkStation)))
	{
		StationStruct.HiredID = Villagers.IndexOfByKey(Village->GetWorkerAt(WorkStation));
	}
	OnVillagersUpdated.ExecuteIfBound(VisualStructs, StationStruct);
}

void UEmploymentVisualInfo::InvokeInitial()
{
	RecieveUpdatedVillagers(Village->GetAllVillagers());
}

void UEmploymentVisualInfo::RegisterEmployment(int VillagerID)
{
	Village->ManageEmployment(WorkStation, VillagerID);
}

void UEmploymentVisualInfo::Clear()
{
	Super::Clear();
	Village->OnVillagersUpdated.Unbind();
	WorkStation = nullptr;
	Village = nullptr;
	OnVillagersUpdated.Unbind();
}
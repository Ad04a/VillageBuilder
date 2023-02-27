// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/Employment/EmployeeMenuWidgetBase.h"
#include "UI/Widgets/Gameplay/Employment/EmployeeWidgetBase.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

void UEmployeeMenuWidgetBase::Init(UVisualizationInfo* VisualInfo)
{
	UEmploymentVisualInfo* EmploymentInfo = Cast<UEmploymentVisualInfo>(VisualInfo);
	if (IsValid(EmploymentInfo) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UEmployeeMenuWidgetBase::Init Givne info type doesnt match"));
		return;
	}
	OnVillagerEmployed.BindDynamic(EmploymentInfo, &UEmploymentVisualInfo::RegisterEmployment);
	EmploymentInfo->OnVillagersUpdated.BindDynamic(this, &UEmployeeMenuWidgetBase::LoadVillagerWidgets);
	EmploymentInfo->InvokeInitial();
}

void UEmployeeMenuWidgetBase::LoadVillagerWidgets(TArray<FVillagerVisualInfoStruct> Villagers, FStationStruct StationStruct)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UEmployeeMenuWidgetBase::LoadVillagerWidgets IsValid(World) == false"));
		return;
	}

	StationName->SetText(StationStruct.StationName);

	VillagerScrollBox->ClearChildren();
	UEmployeeWidgetBase* EmployeeWidget = nullptr;
	int i = 0;
	for (FVillagerVisualInfoStruct Villager : Villagers)
	{
		EmployeeWidget = Cast<UEmployeeWidgetBase>(CreateWidget<UUserWidget>(World, EmployeeWidgetClass));
		if (IsValid(EmployeeWidget) == false) {
			UE_LOG(LogTemp, Error, TEXT("UEmployeeMenuWidgetBase::LoadVillagerWidgets IsValid(EmployeeWidget) == false"));
			continue;
		}
		EmployeeWidget->Init(Villager, StationStruct.ScalingMap, (i==StationStruct.HiredID));
		EmployeeWidget->OnManageButtonClicked.BindDynamic(this, &UEmployeeMenuWidgetBase::ManageButtonClicked);
		VillagerScrollBox->AddChild(EmployeeWidget);
		i++;
	}
}


void UEmployeeMenuWidgetBase::ManageButtonClicked(UEmployeeWidgetBase* EmitterWidget)
{
	if (IsValid(EmitterWidget) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEmployeeMenuWidgetBase::ManageButtonClicked IsValid(EmitterWidget) == false"));
	}
	OnVillagerEmployed.ExecuteIfBound(VillagerScrollBox->GetChildIndex(EmitterWidget));
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/EmployeeMenuWidgetBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UEmployeeMenuWidgetBase::Init(ABaseWorkStation* WorkStation)
{
	CurrentWorkStation = WorkStation;
	StationName->SetText(CurrentWorkStation->GetName());
}

void UEmployeeMenuWidgetBase::LoadVillagerWidgets(TArray<AVillager*> Villagers)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UEmployeeMenuWidgetBase::LoadVillagerWidgets IsValid(World) == false"));
		return;
	}
	if (IsValid(CurrentWorkStation) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UEmployeeMenuWidgetBase::LoadVillagerWidgets IsValid(CurrentWorkStation) == false"));
		return;
	}
	VillagerScrollBox->ClearChildren();
	UEmployeeWidgetBase* EmployeeWidget = nullptr;
	for (AVillager* Villager : Villagers)
	{
		EmployeeWidget = Cast<UEmployeeWidgetBase>(CreateWidget<UUserWidget>(World, EmployeeWidgetClass));
		if (IsValid(EmployeeWidget) == false) {
			UE_LOG(LogTemp, Error, TEXT("UEmployeeMenuWidgetBase::LoadVillagerWidgets IsValid(EmployeeWidget) == false"));
			continue;
		}
		EmployeeWidget->Init(Villager, CurrentWorkStation);
		EmployeeWidget->OnManageButtonClicked.BindDynamic(this, &UEmployeeMenuWidgetBase::ManageButtonClicked);
		VillagerScrollBox->AddChild(EmployeeWidget);

	}
}

void UEmployeeMenuWidgetBase::ManageButtonClicked(AVillager* Villager)
{
	OnVillagerEmployed.ExecuteIfBound(CurrentWorkStation, Villager);
}
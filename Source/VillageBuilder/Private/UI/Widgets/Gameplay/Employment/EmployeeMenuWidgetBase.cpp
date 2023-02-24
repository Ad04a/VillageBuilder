// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/Employment/EmployeeMenuWidgetBase.h"
#include "UI/Widgets/Gameplay/Employment/EmployeeWidgetBase.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

void UEmployeeMenuWidgetBase::Init()
{
	/*CurrentWorkStation = WorkStation;
	StationName->SetText(CurrentWorkStation->GetName());*/
}

void UEmployeeMenuWidgetBase::LoadVillagerWidgets()
{
	/*UWorld* World = GetWorld();
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

	}*/
}

void UEmployeeMenuWidgetBase::ManageButtonClicked(UEmployeeWidgetBase* EmitterWidget)
{
	if (IsValid(EmitterWidget) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEmployeeMenuWidgetBase::ManageButtonClicked IsValid(EmitterWidget) == false ChildIndex: %d"), VillagerScrollBox->GetChildIndex(EmitterWidget));
	}
	OnVillagerEmployed.ExecuteIfBound(VillagerScrollBox->GetChildIndex(EmitterWidget));
}
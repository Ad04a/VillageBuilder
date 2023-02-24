// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/Building/BuildingSelectWidgetBase.h"

void UBuildingSelectWidgetBase::NativeOnInitialized()
{
	SelectButton->OnClicked.AddDynamic(this, &UBuildingSelectWidgetBase::ButtonClicked);
}

void UBuildingSelectWidgetBase::Init(FString Name)
{
	BuildingNameText->SetText(FText::FromString(Name));
}

void UBuildingSelectWidgetBase::ButtonClicked()
{
	OnButtonClicked.ExecuteIfBound(BuildingNameText->GetText().ToString());
}
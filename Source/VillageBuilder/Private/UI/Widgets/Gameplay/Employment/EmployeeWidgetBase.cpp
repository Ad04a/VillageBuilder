// Fill out your copyright notice in the Description page of Project Settings.



#include "Styling/SlateColor.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "UI/Widgets/Gameplay/Employment/EmployeeWidgetBase.h"
#include "UI/Widgets/Gameplay/StatsAndTraits/TraitWidgetBase.h"

void UEmployeeWidgetBase::NativeOnInitialized()
{
	ManageButton->OnClicked.AddDynamic(this, &UEmployeeWidgetBase::ManageButtonCliked);
}

void UEmployeeWidgetBase::Init()
{
	TraitWidget->Init();
}


void UEmployeeWidgetBase::ManageButtonCliked()
{
	OnManageButtonClicked.ExecuteIfBound(this);
}

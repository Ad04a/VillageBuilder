// Fill out your copyright notice in the Description page of Project Settings.



#include "UI/Widgets/Gameplay/Employment/EmployeeWidgetBase.h"
#include "UI/Widgets/Gameplay/StatsAndTraits/TraitWidgetBase.h"

#include "Styling/SlateColor.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UEmployeeWidgetBase::NativeOnInitialized()
{
	ManageButton->OnClicked.AddDynamic(this, &UEmployeeWidgetBase::ManageButtonCliked);
}

void UEmployeeWidgetBase::Init(FVillagerVisualInfoStruct VillagerInfo, TMap<TEnumAsByte<ETrait>, float> ScalingMap, bool bIsHired)
{
	TraitWidget->Init(VillagerInfo, ScalingMap);
	if (bIsHired == true)
	{
		ManageButtonText->SetText(FText::FromString("Fire"));
		return;
	}
	ManageButtonText->SetText(FText::FromString("Hire"));
}


void UEmployeeWidgetBase::ManageButtonCliked()
{
	OnManageButtonClicked.ExecuteIfBound(this);
}

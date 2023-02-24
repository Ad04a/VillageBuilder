// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/DataLinks/VisualModuleWidgetBase.h"
#include "UI/Widgets/Gameplay/DataLinks/VisualButtonWidgetBase.h"
#include "DataTransfers/VisualizationInfo.h"

#include "Components/WrapBox.h"
#include "Components/WidgetSwitcher.h"

void UVisualModuleWidgetBase::NativeOnInitialized()
{

}

void UVisualModuleWidgetBase::Init(TArray<UVisualizationInfo*> InVisualizationInfos)
{
	if (InVisualizationInfos.IsEmpty() == true)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UDataLinkWidgetBase::Init IsValid(World) == false"));
		return;
	}
	UVisualButtonWidgetBase* VisualButton;
	for (UVisualizationInfo* VisualInfo : InVisualizationInfos)
	{
		VisualButton = Cast<UVisualButtonWidgetBase>(CreateWidget<UUserWidget>(World, VisualButtonWidgetClass));
		if (IsValid(VisualButton) == false) {
			UE_LOG(LogTemp, Error, TEXT("UDataLinkWidgetBase::Init IsValid(EmployeeWidget) == false"));
			continue;
		}
		//set icon eventually
		VisualButton->OnButtonClicked.BindDynamic(this, &UVisualModuleWidgetBase::VisualButtonClicked);
		ButtonsWrapBox->AddChild(VisualButton);
	}

}

void UVisualModuleWidgetBase::VisualButtonClicked(class UVisualButtonWidgetBase* ButtonClicked)
{
	VisualWidgetSwitcher->SetActiveWidgetIndex(ButtonsWrapBox->GetChildIndex(ButtonClicked));
}
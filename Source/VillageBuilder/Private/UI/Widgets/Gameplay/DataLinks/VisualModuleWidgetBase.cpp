// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/DataLinks/VisualModuleWidgetBase.h"
#include "UI/Widgets/Gameplay/DataLinks/VisualButtonWidgetBase.h"
#include "UI/Widgets/Gameplay/DataLinks/VisualFragmentWidgetBase.h"
#include "DataTransfers/VisualizationInfo.h"

#include "Components/WrapBox.h"
#include "Components/WidgetSwitcher.h"

void UVisualModuleWidgetBase::Init(TMap<TEnumAsByte<EVisualiationTypes>, UVisualizationInfo*> InVisualizationInfos)
{
	if (InVisualizationInfos.IsEmpty() == true)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UVisualModuleWidgetBase::Init IsValid(World) == false"));
		return;
	}
	UVisualButtonWidgetBase* VisualButton;
	UVisualFragmentWidgetBase* VisualFragment;
	for (TPair<TEnumAsByte<EVisualiationTypes>,UVisualizationInfo*> VisualInfo : InVisualizationInfos)
	{
		VisualButton = Cast<UVisualButtonWidgetBase>(CreateWidget<UUserWidget>(World, VisualButtonWidgetClass));
		if (IsValid(VisualButton) == false) {
			UE_LOG(LogTemp, Error, TEXT("UVisualModuleWidgetBase::Init IsValid(EmployeeWidget) == false"));
			continue;
		}
		UMaterialInterface* Icon = *Icons.Find(VisualInfo.Key);
		if (Icon == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("UVisualModuleWidgetBase::Init IsValid(Icon) == false"));
			continue;
		}
		VisualButton->SetIcon(Icon);

		VisualButton->OnButtonClicked.BindDynamic(this, &UVisualModuleWidgetBase::VisualButtonClicked);
		ButtonsWrapBox->AddChild(VisualButton);

		TSubclassOf<UVisualFragmentWidgetBase> FragmentClass = *Fragments.Find(VisualInfo.Key);
		if (FragmentClass == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("UVisualModuleWidgetBase::Init IsValid(FragmentClass) == false"));
			continue;
		}
		VisualFragment = Cast<UVisualFragmentWidgetBase>(CreateWidget<UUserWidget>(World, FragmentClass));
		if (IsValid(VisualFragment) == false) {
			UE_LOG(LogTemp, Error, TEXT("UVisualModuleWidgetBase::Init IsValid(VisualFragment) == false"));
			continue;
		}
		VisualFragment->Init(VisualInfo.Value);
		VisualFragment->OnForceClose.AddDynamic(this, &UVisualModuleWidgetBase::ForceClose);
		VisualWidgetSwitcher->AddChild(VisualFragment);
	}

}

void UVisualModuleWidgetBase::ForceClose()
{
	OnForceClose.Broadcast();
}

void UVisualModuleWidgetBase::VisualButtonClicked(class UVisualButtonWidgetBase* ButtonClicked)
{
	VisualWidgetSwitcher->SetActiveWidgetIndex(ButtonsWrapBox->GetChildIndex(ButtonClicked));
}
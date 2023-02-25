// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/DataLinks/DataLinkWidgetBase.h"
#include "UI/Widgets/Gameplay/DataLinks/VisualModuleWidgetBase.h"
#include "DataTransfers/VisualizationInfo.h"

#include "Components/WrapBox.h"
#include "Components/Button.h"

void UDataLinkWidgetBase::NativeOnInitialized()
{
	CloseButton->OnClicked.AddDynamic(this, &UDataLinkWidgetBase::ButtonClicked);
}

void UDataLinkWidgetBase::Init(TMap<TEnumAsByte<EVisualiationTypes>, UVisualizationInfo*> InitiatorVisualizationInfos, TMap<TEnumAsByte<EVisualiationTypes>, UVisualizationInfo*> TargetVisualizationInfos)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UDataLinkWidgetBase::Init IsValid(World) == false"));
		return;
	}
	
	UVisualModuleWidgetBase*  InitiatorVisualModule = Cast<UVisualModuleWidgetBase>(CreateWidget<UUserWidget>(World, VisualModuleWidgetClass));
	if (IsValid(InitiatorVisualModule) == false) {
		UE_LOG(LogTemp, Error, TEXT("UDataLinkWidgetBase::Init IsValid(InitiatorVisualModule) == false"));
		return;
	}
	InitiatorVisualModule->Init(InitiatorVisualizationInfos);
	

	UVisualModuleWidgetBase* TargetVisualModule = Cast<UVisualModuleWidgetBase>(CreateWidget<UUserWidget>(World, VisualModuleWidgetClass));
	if (IsValid(TargetVisualModule) == false) {
		UE_LOG(LogTemp, Error, TEXT("UDataLinkWidgetBase::Init IsValid(TargetVisualModule) == false"));
		return;
	}
	TargetVisualModule->Init(TargetVisualizationInfos);

	ModuleWrapBox->AddChild(TargetVisualModule);
	ModuleWrapBox->AddChild(InitiatorVisualModule);

}

void UDataLinkWidgetBase::ButtonClicked()
{
	ModuleWrapBox->ClearChildren();
	OnLinkClosed.Broadcast();
}
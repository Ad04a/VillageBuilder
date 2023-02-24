// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/DataLinks/DataLinkWidgetBase.h"
#include "UI/Widgets/Gameplay/DataLinks/VisualModuleWidgetBase.h"
#include "DataTransfers/VisualizationInfo.h"

#include "Components/WrapBox.h"

void UDataLinkWidgetBase::NativeOnInitialized()
{

}

void UDataLinkWidgetBase::Init(TArray<UVisualizationInfo*> InitiatorVisualizationInfos, TArray<UVisualizationInfo*> TargetVisualizationInfos)
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
	}
	InitiatorVisualModule->Init(InitiatorVisualizationInfos);
	ModuleWrapBox->AddChild(InitiatorVisualModule);
	
	UVisualModuleWidgetBase* TargetVisualModule = Cast<UVisualModuleWidgetBase>(CreateWidget<UUserWidget>(World, VisualModuleWidgetClass));
	if (IsValid(TargetVisualModule) == false) {
		UE_LOG(LogTemp, Error, TEXT("UDataLinkWidgetBase::Init IsValid(TargetVisualModule) == false"));
	}
	TargetVisualModule->Init(TargetVisualizationInfos);
	ModuleWrapBox->AddChild(TargetVisualModule);

}
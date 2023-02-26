// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/MainPurpose/InGameOptionsWidgetBase.h"
#include "DataTransfers/VisualizationInfos/OptionsVisualInfo.h"

#include "Components/Button.h"

void UInGameOptionsWidgetBase::Init(UVisualizationInfo* VisualInfo)
{
	UOptionsVisualInfo* OptionsInfo = Cast<UOptionsVisualInfo>(VisualInfo);
	if (IsValid(OptionsInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTraitMenuWidgetBase::Init Given VisualInfo doesnt mach the required type"));
	}
	ExitButton->OnClicked.AddDynamic(OptionsInfo, &UOptionsVisualInfo::ExitGame);
}

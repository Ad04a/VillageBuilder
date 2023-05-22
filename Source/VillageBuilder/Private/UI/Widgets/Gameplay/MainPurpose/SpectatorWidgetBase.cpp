// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/MainPurpose/SpectatorWidgetBase.h"
#include "DataTransfers/VisualizationInfos/SpectatorVisualInfo.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void USpectatorWidgetBase::Init(UVisualizationInfo* VisualInfo)
{
	USpectatorVisualInfo* SpectatorInfo = Cast<USpectatorVisualInfo>(VisualInfo);
	if (IsValid(SpectatorInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("USpectatorWidgetBase::Init Given VisualInfo doesnt mach the required type"));
	}
	DeleteButton->OnClicked.AddDynamic(SpectatorInfo, &USpectatorVisualInfo::DeleteSave);

	SurvivedTime->SetText(FText::FromString(FString::FromInt(int(SpectatorInfo->GetTimeSurvived() / 150)) + " days"));
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/MainPurpose/MainPurposeWidgetBase.h"
#include "UI/Widgets/Gameplay/StatsAndTraits/StatWidgetBase.h"
#include "Components/TextBlock.h"

void UMainPurposeWidgetBase::PassStatUpdate(EStat StatName, float Current, float Max)
{
	StatWidget->SetStat(StatName, Current, Max);
}


void UMainPurposeWidgetBase::SetInteractionText(FText ActionText)
{
	InteractionText->SetText(ActionText);
}

void UMainPurposeWidgetBase::SetDataLinkText(FText ActionText)
{
	DataLinkText->SetText(ActionText);
}
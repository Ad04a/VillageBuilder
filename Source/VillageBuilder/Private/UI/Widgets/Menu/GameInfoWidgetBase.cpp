// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Menu/GameInfoWidgetBase.h"

void UGameInfoWidgetBase::Init(FString SaveName)
{
	SaveSlotName->SetText(FText::FromString(SaveName.LeftChop(4)));
}

void UGameInfoWidgetBase::NativeOnInitialized()
{

	ContinueButton->OnClicked.AddDynamic(this, &UGameInfoWidgetBase::ContinueButtonCliked);
}

void UGameInfoWidgetBase::ContinueButtonCliked()
{
	OnContinueClicked.ExecuteIfBound(SaveSlotName->GetText().ToString());
}
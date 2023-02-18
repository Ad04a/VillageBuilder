// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/InGameOptionsWidgetBase.h"

void UInGameOptionsWidgetBase::NativeOnInitialized()
{
	ExitButton->OnClicked.AddDynamic(this, &UInGameOptionsWidgetBase::ExitClicked);
	ContinueButton->OnClicked.AddDynamic(this, &UInGameOptionsWidgetBase::ContinueClicked);
}

void UInGameOptionsWidgetBase::ExitClicked()
{
	OnExitClicked.ExecuteIfBound();
}

void UInGameOptionsWidgetBase::ContinueClicked()
{
	OnContinueClicked.ExecuteIfBound();
}
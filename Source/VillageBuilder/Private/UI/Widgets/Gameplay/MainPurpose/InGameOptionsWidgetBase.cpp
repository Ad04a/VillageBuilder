// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/MainPurpose/InGameOptionsWidgetBase.h"
#include "Components/Button.h"

void UInGameOptionsWidgetBase::NativeOnInitialized()
{
	ExitButton->OnClicked.AddDynamic(this, &UInGameOptionsWidgetBase::ExitClicked);
}

void UInGameOptionsWidgetBase::ExitClicked()
{
	OnExitClicked.ExecuteIfBound();
}

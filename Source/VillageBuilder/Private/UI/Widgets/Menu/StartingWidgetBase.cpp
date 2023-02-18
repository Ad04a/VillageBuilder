// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Menu/StartingWidgetBase.h"
#include "Kismet/GameplayStatics.h"

void UStartingWidgetBase::OnPlayClicked()
{
	PlayClicked.Broadcast();
}

void UStartingWidgetBase::OnQuitClicked()
{
	QuitClicked.Broadcast();
}

void UStartingWidgetBase::NativeOnInitialized()
{
	Quit->OnClicked.AddDynamic(this, &UStartingWidgetBase::OnQuitClicked);
	Play->OnClicked.AddDynamic(this, &UStartingWidgetBase::OnPlayClicked);
}

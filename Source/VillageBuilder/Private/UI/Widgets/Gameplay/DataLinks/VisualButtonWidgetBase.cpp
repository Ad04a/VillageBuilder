// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/DataLinks/VisualButtonWidgetBase.h"

#include "Components/image.h"
#include "Components/Button.h"

void UVisualButtonWidgetBase::NativeOnInitialized()
{
	VisualButton->OnClicked.AddDynamic(this, &UVisualButtonWidgetBase::ButtonClicked);
}

void UVisualButtonWidgetBase::ButtonClicked()
{
	OnButtonClicked.ExecuteIfBound(this);
}

void UVisualButtonWidgetBase::SetIcon(UMaterialInterface* Image)
{
	Icon->SetBrushFromMaterial(Image);
}
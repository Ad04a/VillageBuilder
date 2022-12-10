// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/InteractionWidgetBase.h"


void UInteractionWidgetBase::UpdateInteractionText(FText ActionText) {
	InteractionText->SetText(ActionText);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/MainPurpose/RequestModuleWidgetBase.h"

#include "Components/TextBlock.h"

void URequestModuleWidgetBase::Init(FString Class, int Quantity)
{

	FString Name = Class;
	if (Class.Contains("_C", ESearchCase::IgnoreCase, ESearchDir::FromEnd) == true)
	{
		Name = Name.LeftChop(2);
	}
	if (Class.Contains("BP_", ESearchCase::IgnoreCase, ESearchDir::FromStart) == true)
	{
		Name = Name.RightChop(3);
	}
	ItemName->SetText(FText::FromString(Name));

	if (Quantity == 0)
	{
		return;
	}
	ItemCount->SetText(FText::FromString(FString::FromInt(Quantity)));
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Menu/NewSaveWidgetBase.h"

void UNewSaveWidgetBase::NativeOnInitialized()
{
	SaveName->OnTextChanged.AddDynamic(this, &UNewSaveWidgetBase::MangeEnteredText);
	BackButton->OnClicked.AddDynamic(this, &UNewSaveWidgetBase::BackClicked);
	CreateButton->OnClicked.AddDynamic(this, &UNewSaveWidgetBase::CreateClicked);
}

void UNewSaveWidgetBase::NativeConstruct()
{
	SaveName->SetText(FText::FromString(""));
	ErrorText->SetText(FText::FromString(""));
}

void UNewSaveWidgetBase::MangeEnteredText(const FText& Text)
{
	bCanCreate = false;
	ErrorText->SetText(FText::FromString(""));

	if (SaveName->GetText().ToString().Len() < MinNameLenght)
	{
		ErrorText->SetText(FText::FromString("Name should be atleast " + FString::FromInt(MinNameLenght) + " symbols"));
		return;
	}
	if (SaveName->GetText().ToString().Len() < MaxNameLenght)
	{
		bCanCreate = true;
		return;
	}
	FString Name = Text.ToString();
	ErrorText->SetText(FText::FromString(Name.LeftChop(Name.Len() - MaxNameLenght)));
}

void UNewSaveWidgetBase::CreateClicked()
{
	if (bCanCreate == false)
	{
		return;
	}
	OnCreateClicked.ExecuteIfBound(SaveName->GetText().ToString());
}


void UNewSaveWidgetBase::BackClicked()
{
	OnBackClicked.ExecuteIfBound();
}

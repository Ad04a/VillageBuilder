// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Menu/ChooseSaveGameWidgetBase.h"

void UChooseSaveGameWidgetBase::NativeOnInitialized()
{
	BackButton->OnClicked.AddDynamic(this, &UChooseSaveGameWidgetBase::BackClicked);
	CreateButton->OnClicked.AddDynamic(this, &UChooseSaveGameWidgetBase::CreateClicked);
}

void UChooseSaveGameWidgetBase::Init(TArray<FString> SaveSlots)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UChooseSaveGameWidgetBase::Init IsValid(World) == false"));
		return;
	}
	SaveGamesScrollBox->ClearChildren();
	UGameInfoWidgetBase* GameInfoWidget = nullptr;

	for (FString SaveName : SaveSlots)
	{
		GameInfoWidget = Cast<UGameInfoWidgetBase>(CreateWidget<UUserWidget>(World, GameInfoWidgetBaseClass));
		if (IsValid(GameInfoWidget) == false) {
			UE_LOG(LogTemp, Error, TEXT("UChooseSaveGameWidgetBase::Init IsValid(GameInfoWidget) == false"));
			continue;
		}
		GameInfoWidget->Init(SaveName);
		GameInfoWidget->OnContinueClicked.BindDynamic(this, &UChooseSaveGameWidgetBase::RegisterChosenSave);
		SaveGamesScrollBox->AddChild(GameInfoWidget);

	}
}

void UChooseSaveGameWidgetBase::RegisterChosenSave(FString SaveName)
{
	OnSlotSelected.ExecuteIfBound(SaveName);
}

void UChooseSaveGameWidgetBase::BackClicked()
{
	OnBackClicked.ExecuteIfBound();
}

void UChooseSaveGameWidgetBase::CreateClicked()
{
	OnCreateClicked.ExecuteIfBound();
}

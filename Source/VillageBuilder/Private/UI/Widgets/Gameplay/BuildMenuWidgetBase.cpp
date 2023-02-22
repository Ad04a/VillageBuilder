// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/BuildMenuWidgetBase.h"
#include "UI/Widgets/Gameplay/BuildingSelectWidgetBase.h"

void UBuildMenuWidgetBase::NativeOnInitialized()
{
	CloseButton->OnClicked.AddDynamic(this, &UBuildMenuWidgetBase::CloseClicked);
}

void UBuildMenuWidgetBase::Init(TArray<FString> Buildings)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBuildMenuWidgetBase::Init IsValid(World) == false"));
		return;
	}
	BuildingScrollBox->ClearChildren();

	UBuildingSelectWidgetBase* BuildingWidget = nullptr;
	for (FString Name : Buildings)
	{
		BuildingWidget = Cast<UBuildingSelectWidgetBase>(CreateWidget<UUserWidget>(World, BuildingSelectClass));
		if (IsValid(BuildingWidget) == false) {
			UE_LOG(LogTemp, Error, TEXT("UBuildMenuWidgetBase::Init IsValid(BuildingWidget) == false"));
			continue;
		}
		BuildingWidget->Init(Name);
		BuildingWidget->OnButtonClicked.BindDynamic(this, &UBuildMenuWidgetBase::BuildingSelected);
		BuildingScrollBox->AddChild(BuildingWidget);
	}
}

void UBuildMenuWidgetBase::BuildingSelected(FString SelectedBuildingName)
{
	if (OnBuildingSelected.IsBound() == false)
	{
		return;
	}
	if (OnBuildingSelected.Execute(SelectedBuildingName) == false)
	{
	}
	OnCloseSignal.ExecuteIfBound();
}

void UBuildMenuWidgetBase::CloseClicked()
{
	OnCloseSignal.ExecuteIfBound();
}
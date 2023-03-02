// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/Building/BuildMenuWidgetBase.h"
#include "UI/Widgets/Gameplay/Building/BuildingSelectWidgetBase.h"
#include "DataTransfers/VisualizationInfos/BuildingVisualInfo.h"

#include "Components/ScrollBox.h"
#include "Components/Button.h"


void UBuildMenuWidgetBase::Init(UVisualizationInfo* VisualInfo)
{
	UBuildingVisualInfo* BuildingInfo = Cast<UBuildingVisualInfo>(VisualInfo);

	BuildingScrollBox->ClearChildren();

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBuildMenuWidgetBase::Init IsValid(World) == false"));
		return;
	}
	OnBuildingSelected.BindDynamic(BuildingInfo, &UBuildingVisualInfo::BuildingSelected);
	UBuildingSelectWidgetBase* BuildingWidget = nullptr;
	for (FString Name : BuildingInfo->GetBuildingNames())
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
	OnBuildingSelected.Execute(SelectedBuildingName);
	ForceClose();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/Building/ConstructionWidgetBase.h"
#include "DataTransfers/VisualizationInfos/ConstructionVisualInfo.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UConstructionWidgetBase::Init(UVisualizationInfo* VisualInfo)
{
	UConstructionVisualInfo* ConstructionInfo = Cast<UConstructionVisualInfo>(VisualInfo); 
	ConstructionInfo->OnStatusChanged.BindDynamic(this, &UConstructionWidgetBase::SetManageText);
	ManageButton->OnClicked.AddDynamic(ConstructionInfo, &UConstructionVisualInfo::StartBuild);
	ConstructionInfo->GetInitialState();

	StationName->SetText(ConstructionInfo->GetName());

}

void UConstructionWidgetBase::SetManageText(FText Text)
{
	ButtonText->SetText(Text);
}
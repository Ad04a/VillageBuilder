// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/Employment/InviteWidgetBase.h"
#include "DataTransfers/VisualizationInfos/InviteVisualInfo.h"

#include "Components/Button.h"

void UInviteWidgetBase::Init(class UVisualizationInfo* VisualInfo)
{
	UInviteVisualInfo* InviteInfo = Cast<UInviteVisualInfo>(VisualInfo);
	if (IsValid(InviteInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInviteWidgetBase::Init Given VisualInfo doesnt mach the required type"));
	}
	InviteButton->OnClicked.AddDynamic(InviteInfo, &UInviteVisualInfo::InviteVillager);
}
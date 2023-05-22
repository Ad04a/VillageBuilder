// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/MainPurpose/RequestMenuWidgetBase.h"
#include "DataTransfers/VisualizationInfos/RequestVisualInfo.h"
#include "UI/Widgets/Gameplay/MainPurpose/RequestWidgetBase.h"

#include "Components/ScrollBox.h"

void URequestMenuWidgetBase::Init(UVisualizationInfo* VisualInfo)
{
	URequestVisualInfo* RequestInfo = Cast<URequestVisualInfo>(VisualInfo);
	if (IsValid(RequestInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("URequestMenuWidgetBase::Init Given VisualInfo doesnt mach the required type"));
	}
	RequestInfo->OnRequestUpdated.BindDynamic(this, &URequestMenuWidgetBase::GetUpdatedRequests);
	OnUpdateNeeded.BindDynamic(RequestInfo, &URequestVisualInfo::GetUpdate);
}

void URequestMenuWidgetBase::GetUpdatedRequests(TArray<FVisualRequest> Requests)
{
	VillagerScrollBox->ClearChildren();

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT(" URequestMenuWidgetBase::GetUpdatedRequests IsValid(World) == false"));
		return;
	}

	for (FVisualRequest Request : Requests)
	{
		URequestWidgetBase* RequestWidget = CreateWidget<URequestWidgetBase>(World, RequestWidgetClass);
		RequestWidget->Init(Request.Villager, Request.Classes, Request.IsFull);
		VillagerScrollBox->AddChild(RequestWidget);
	}
}

void URequestMenuWidgetBase::NativeConstruct()
{
	OnUpdateNeeded.ExecuteIfBound();
}
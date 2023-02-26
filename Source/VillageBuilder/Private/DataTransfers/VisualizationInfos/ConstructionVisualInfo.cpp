// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/ConstructionVisualInfo.h"
#include "WorkSystem/BaseWorkStation.h"
#include "Components/BuildingClusterComponent.h"

UVisualizationInfo* UConstructionVisualInfo::CreateVisualInfo(AActor* InActor)
{
	UConstructionVisualInfo* Info = NewObject<UConstructionVisualInfo>();
	if (IsValid(Info) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UConstructionVisualInfo::CreateVisualInfo Cannot create info"));
		return nullptr;
	}
	Info->WorkStation = Cast<ABaseWorkStation>(InActor);
	if (IsValid(Info->WorkStation) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UConstructionVisualInfo::CreateVisualInfo Cannot create info: Actor is not ABaseWorkStation"));
		return nullptr;
	}
	Info->WorkStation->OnStartedConstruction.AddDynamic(Info, &UConstructionVisualInfo::CaptureState);
	return Info;
}

void UConstructionVisualInfo::CaptureState(bool State, ABaseWorkStation* InWorkStation)
{
	FText Text = FText::FromString("Start Construction");
	if (State == true)
	{
		Text = FText::FromString("Stop Construction");
	}
	OnStatusChanged.ExecuteIfBound(Text);
}

FText UConstructionVisualInfo::GetName() 
{ 
	return WorkStation->GetName(); 
}

void UConstructionVisualInfo::StartBuild() 
{ 
	return WorkStation->StartBuild(); 
}

void UConstructionVisualInfo::GetInitialState()
{
	CaptureState(WorkStation->GetIsConstructing(), WorkStation);
}

void UConstructionVisualInfo::Clear()
{
	WorkStation->OnStartedConstruction.RemoveDynamic(this, &UConstructionVisualInfo::CaptureState);
	WorkStation = nullptr;
	OnStatusChanged.Unbind();
}
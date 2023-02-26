// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/EmploymentVisualInfo.h"

UVisualizationInfo* UEmploymentVisualInfo::CreateVisualInfo(AActor* InActor)
{
	UEmploymentVisualInfo* Info = NewObject<UEmploymentVisualInfo>();
	if (IsValid(Info) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UEmploymentVisualInfo::CreateVisualInfo Cannot create info"));
		return nullptr;
	}

	return Info;
}

void UEmploymentVisualInfo::Clear()
{
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/InventoryVisualInfo.h"

UVisualizationInfo* UInventoryVisualInfo::CreateVisualInfo(AActor* InActor)
{
	UInventoryVisualInfo* Info = NewObject<UInventoryVisualInfo>();
	if (IsValid(Info) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryVisualInfo::CreateVisualInfo Cannot create info for %s of class %s"), *InActor->GetName(), *InActor->GetClass()->GetName());
		return nullptr;
	}

	return Info;
}

void UInventoryVisualInfo::Clear()
{
	Super::Clear();
}
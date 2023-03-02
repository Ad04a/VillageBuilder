// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTransfers/VisualizationInfo.h"
#include "BuildingVisualInfo.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBuildingVisualInfo : public UVisualizationInfo
{
	GENERATED_BODY()

protected:
	class ABuilderItem* Item;
	TMap<FString, FName> BuildingsInfo;
public:
	static UVisualizationInfo* CreateVisualInfo(AActor* InActor);
	virtual void Clear() override;
	TArray<FString> GetBuildingNames();

	UFUNCTION()
	void BuildingSelected(FString BuildingName);
};

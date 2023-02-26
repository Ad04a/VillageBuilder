// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTransfers/VisualizationInfo.h"
#include "EmploymentVisualInfo.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UEmploymentVisualInfo : public UVisualizationInfo
{
	GENERATED_BODY()
	
public:
	static UVisualizationInfo* CreateVisualInfo(AActor* InActor);
	virtual void Clear() override;
};

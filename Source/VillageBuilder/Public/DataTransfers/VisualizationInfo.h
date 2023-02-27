// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VisualizationInfo.generated.h"


UCLASS(Abstract)
class VILLAGEBUILDER_API UVisualizationInfo : public UObject
{
	GENERATED_BODY()
public:
	virtual void Clear() { ConditionalBeginDestroy();}
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTransfers/VisualizationInfo.h"
#include "ConstructionVisualInfo.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FConstructionStatusSignature, FText, Status);

UCLASS()
class VILLAGEBUILDER_API UConstructionVisualInfo : public UVisualizationInfo
{
	GENERATED_BODY()
protected:
	class ABaseWorkStation* WorkStation;

	UFUNCTION()
	void CaptureState(bool State, ABaseWorkStation* InWorkStation);

public:
	static UVisualizationInfo* CreateVisualInfo(AActor* InActor);
	virtual void Clear() override;

	FConstructionStatusSignature OnStatusChanged;

	FText GetName();
	UFUNCTION()
	void StartBuild();
	void GetInitialState();
};

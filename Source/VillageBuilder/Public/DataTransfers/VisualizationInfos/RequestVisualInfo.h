// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTransfers/VisualizationInfo.h"

#include "Headers/RequestVisual.h"

#include "RequestVisualInfo.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FNewRequestSygnature, TArray<FVisualRequest>,Requests);
DECLARE_DYNAMIC_DELEGATE(FGetUpdateSignature);

UCLASS()
class VILLAGEBUILDER_API URequestVisualInfo : public UVisualizationInfo
{
	GENERATED_BODY()
protected:

	UFUNCTION()
	void RecieveUpdate(TArray<struct FRequest> Requests);

	FGetUpdateSignature OnGetUpdates;

public:

	UFUNCTION()
	void GetUpdate();

	FNewRequestSygnature OnRequestUpdated;

	static UVisualizationInfo* CreateVisualInfo(AActor* InActor);
	virtual void Clear() override;
	
};

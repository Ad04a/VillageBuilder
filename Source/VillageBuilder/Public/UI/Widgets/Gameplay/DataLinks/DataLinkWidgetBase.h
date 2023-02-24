// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataLinkWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UDataLinkWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<class UVisualModuleWidgetBase> VisualModuleWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UWrapBox* ModuleWrapBox;

public:
	void Init(TArray<class UVisualizationInfo*> InitiatorVisualizationInfos, TArray<class UVisualizationInfo*> TargetVisualizationInfos);
	void NativeOnInitialized() override;
};

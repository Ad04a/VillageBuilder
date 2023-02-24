// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VisualModuleWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UVisualModuleWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<class UVisualButtonWidgetBase> VisualButtonWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UWrapBox* ButtonsWrapBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UWidgetSwitcher* VisualWidgetSwitcher;

	UFUNCTION()
	void VisualButtonClicked(class UVisualButtonWidgetBase* ButtonClicked);

public:
	void Init(TArray<class UVisualizationInfo*> InVisualizationInfos);
	void NativeOnInitialized() override;
};

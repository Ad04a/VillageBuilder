// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/VisualizationTypes.h"
#include "VisualModuleWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UVisualModuleWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UWrapBox* ButtonsWrapBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UWidgetSwitcher* VisualWidgetSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UVisualButtonWidgetBase> VisualButtonWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<EVisualiationTypes>, UMaterialInterface*> Icons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<EVisualiationTypes>, TSubclassOf<class UVisualFragmentWidgetBase>> Fragments;

	UFUNCTION()
	void VisualButtonClicked(class UVisualButtonWidgetBase* ButtonClicked);

public:
	void Init(TMap<TEnumAsByte<EVisualiationTypes>, class UVisualizationInfo*> InVisualizationInfos);
	void NativeOnInitialized() override;
};

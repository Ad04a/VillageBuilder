// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/Widgets/Gameplay/DataLinks/VisualFragmentWidgetBase.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Characters/Villager.h"
#include "TraitMenuWidgetBase.generated.h"

/**
 * 
 */

UCLASS()
class VILLAGEBUILDER_API UTraitMenuWidgetBase : public UVisualFragmentWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTraitWidgetBase* TraitWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UStatWidgetBase* StatWidget;

public:
	virtual void Init(class UVisualizationInfo* VisualInfo) override;
};

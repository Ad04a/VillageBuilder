// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/Widgets/Gameplay/DataLinks/VisualFragmentWidgetBase.h"
#include "Components/ScrollBox.h"
#include "InventoryWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UInventoryWidgetBase : public UVisualFragmentWidgetBase
{
	GENERATED_BODY()
private:
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UScrollBox* InventoryScrollBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UInventoryRowWidgetBase> InventoryRowClass;


public:
	virtual void Init(class UVisualizationInfo* VisualInfo) override;
};

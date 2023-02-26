// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Gameplay/DataLinks/VisualFragmentWidgetBase.h"
#include "ConstructionWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UConstructionWidgetBase : public UVisualFragmentWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* ManageButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* StationName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ButtonText;

public:
	virtual void Init(class UVisualizationInfo* VisualInfo) override;

	UFUNCTION()
	void SetManageText(FText Text);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Gameplay/DataLinks/VisualFragmentWidgetBase.h"
#include "SpectatorWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API USpectatorWidgetBase : public UVisualFragmentWidgetBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* DeleteButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* SpectateButton;

public:
	virtual void Init(class UVisualizationInfo* VisualInfo) override;

};

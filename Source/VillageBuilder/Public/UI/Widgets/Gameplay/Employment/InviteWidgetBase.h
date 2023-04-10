// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Gameplay/DataLinks/VisualFragmentWidgetBase.h"
#include "InviteWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UInviteWidgetBase : public UVisualFragmentWidgetBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* InviteButton;

public:
	virtual void Init(class UVisualizationInfo* VisualInfo) override;
};

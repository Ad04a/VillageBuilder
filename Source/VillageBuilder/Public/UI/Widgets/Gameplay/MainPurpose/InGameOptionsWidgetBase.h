// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/Widgets/Gameplay/DataLinks/VisualFragmentWidgetBase.h"
#include "InGameOptionsWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE(FButtunClickedSignature);

UCLASS()
class VILLAGEBUILDER_API UInGameOptionsWidgetBase : public UVisualFragmentWidgetBase
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* ExitButton;

public:
	virtual void Init(class UVisualizationInfo* VisualInfo) override;

};

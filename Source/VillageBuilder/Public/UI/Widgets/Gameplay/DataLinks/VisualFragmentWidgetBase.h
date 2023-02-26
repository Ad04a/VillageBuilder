// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VisualFragmentWidgetBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FForceCloseSignature);

UCLASS(Abstract)
class VILLAGEBUILDER_API UVisualFragmentWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	FForceCloseSignature OnForceClose;
	virtual void ForceClose() { OnForceClose.Broadcast(); }
	virtual void Init(class UVisualizationInfo* VisualInfo) PURE_VIRTUAL(UVisualFragmentWidgetBase::Init, );
};

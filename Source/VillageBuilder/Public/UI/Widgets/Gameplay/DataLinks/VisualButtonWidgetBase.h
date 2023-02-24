// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VisualButtonWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FButtonChosenSignature, UVisualButtonWidgetBase*, ClickedButton);

UCLASS()
class VILLAGEBUILDER_API UVisualButtonWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* VisualButton;

	UFUNCTION()
	void ButtonClicked();

public:
	FButtonChosenSignature OnButtonClicked;
	void NativeOnInitialized() override;
};

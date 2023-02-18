// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "InGameOptionsWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE(FButtunClickedSignature);

UCLASS()
class VILLAGEBUILDER_API UInGameOptionsWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* ExitButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* ContinueButton;

	UFUNCTION()
	void ExitClicked();

	UFUNCTION()
	void ContinueClicked();

public:
	FButtunClickedSignature OnExitClicked;
	FButtunClickedSignature OnContinueClicked;

	void NativeOnInitialized()override;
};

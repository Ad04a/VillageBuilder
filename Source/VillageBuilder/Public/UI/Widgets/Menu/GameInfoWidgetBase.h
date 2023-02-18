// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GameInfoWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FGameInfoButtonClicked, FString, GameSlotName);

UCLASS()
class VILLAGEBUILDER_API UGameInfoWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* ContinueButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* SaveSlotName;

	UFUNCTION()
	void ContinueButtonCliked();

public:
	void NativeOnInitialized() override;
	FGameInfoButtonClicked OnContinueClicked;
	void Init(FString SaveName);
};

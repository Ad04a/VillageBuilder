// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/StatAndTraitEnums.h"
#include "MainPurposeWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UMainPurposeWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UStatWidgetBase* StatWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UInventoryRowWidgetBase* InventoryWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* InteractionText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* DataLinkText;

public:
	UFUNCTION()
	void PassStatUpdate(EStat StatName, float Current, float Max);

	UFUNCTION()
	void SetInteractionText(FText ActionText);

	UFUNCTION()
	void SetDataLinkText(FText ActionText);
};

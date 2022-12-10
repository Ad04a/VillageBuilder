// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "InteractionWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UInteractionWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* InteractionText;

public:
	UFUNCTION()
	void UpdateInteractionText(FText ActionText);

};

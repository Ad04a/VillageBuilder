// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RequestModuleWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API URequestModuleWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ItemCount;

public:
	void Init(FString Class, int Quantity);
};

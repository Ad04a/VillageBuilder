// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/InventoryDropEvent.h"
#include "InventorySlotWidgetBase.generated.h"


UCLASS()
class VILLAGEBUILDER_API UInventorySlotWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:

	FDropStartedSignature OnDropStarted;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};

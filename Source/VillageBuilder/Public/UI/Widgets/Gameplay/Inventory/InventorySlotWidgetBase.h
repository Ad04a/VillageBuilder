// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FDropStaredSignature, UInventorySlotWidgetBase*, DropedPoint, UObject*, Payload);

UCLASS()
class VILLAGEBUILDER_API UInventorySlotWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:

	FDropStaredSignature OnDropStarted;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};

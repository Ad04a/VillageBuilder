// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/InventoryDropEvent.h"
#include "InventoryDropSpaceWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UInventoryDropSpaceWidgetBase : public UUserWidget
{
	GENERATED_BODY()
private:
protected:

	UPROPERTY(EditDefaultsOnly, Category = DragDrop, meta = (BindWidget))
	class UBorder* DropBackground;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor NormalColor;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor HoverColor;

public:
	FDropStartedSignature OnDropStarted;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* OutOperation) override;
	void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};

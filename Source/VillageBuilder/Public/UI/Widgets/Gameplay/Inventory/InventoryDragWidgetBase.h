// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/InventoryDropEvent.h"
#include "InventoryDragWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(UObject*, FDragStaredSignature, UInventoryDragWidgetBase*, DragedChild, class UDragDropOperation*, InOperation);

UCLASS()
class VILLAGEBUILDER_API UInventoryDragWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly, Category = DragDrop, meta = (BindWidget))
	class UImage* ItemIcon;

	UPROPERTY(EditDefaultsOnly, Category = DragDrop, meta = (BindWidget))
	class UBorder* ItemBorder;	

	UPROPERTY(EditDefaultsOnly)
	FLinearColor NormalColor;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor HoverColor;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor DragingColor;

public:

	FDragStaredSignature OnDragStarted;
	FDropStartedSignature OnDropStarted;

	void Init(class UMaterialInterface* Icon, FVector2D InSize = FVector2D(55,55));
	void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void NativeOnDragDetected(const FGeometry& InGeometry,  const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};

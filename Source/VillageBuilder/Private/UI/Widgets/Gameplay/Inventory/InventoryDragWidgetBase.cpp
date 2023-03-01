// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/Inventory/InventoryDragWidgetBase.h"
#include "Items/StoredItemInfo.h"

#include "Components/Image.h"
#include "Components/Border.h"
#include "Blueprint/DragDropOperation.h"

void UInventoryDragWidgetBase::Init(UMaterialInterface* Icon)
{
	ItemIcon->SetBrushFromMaterial(Icon);
}

void UInventoryDragWidgetBase::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	ItemBorder->SetBrushColor(NormalColor);
}

void UInventoryDragWidgetBase::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	ItemBorder->SetBrushColor(HoverColor);
}

FReply UInventoryDragWidgetBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
		return Reply;
	}
	return Reply;
}

void UInventoryDragWidgetBase::NativeOnDragDetected(const FGeometry& InGeometry,  const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (OnDragStarted.IsBound() == false)
	{
		return;
	}
	ItemBorder->SetBrushColor(DragingColor);
	

	UObject* Payload = Cast<UObject>(OnDragStarted.Execute(this));
	if (IsValid(Payload) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryDragWidgetBase::NativeOnDragDetected IsValid(Payload) == false"));
		return;
	}

	OnDragStarted.Unbind();
	RemoveFromParent();

	UDragDropOperation* DragOperation = NewObject<UDragDropOperation>();
	DragOperation->Payload = Payload;
	DragOperation->DefaultDragVisual = this;
	DragOperation->Pivot = EDragPivot::TopLeft;
	OutOperation = DragOperation;
}
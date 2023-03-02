// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/Inventory/InventoryDropSpaceWidgetBase.h"

#include "Components/Border.h"
#include "Blueprint/DragDropOperation.h"

void UInventoryDropSpaceWidgetBase::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	DropBackground->SetBrushColor(HoverColor);
}

void UInventoryDropSpaceWidgetBase::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	DropBackground->SetBrushColor(NormalColor);
}

bool UInventoryDropSpaceWidgetBase::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	OnDropStarted.ExecuteIfBound(this, InOperation->Payload);
	return true;
}

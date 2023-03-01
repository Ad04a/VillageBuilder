// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/Inventory/InventorySlotWidgetBase.h"

#include "Blueprint/DragDropOperation.h"

bool UInventorySlotWidgetBase::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	OnDropStarted.ExecuteIfBound(this, InOperation->Payload);
	return true;
}
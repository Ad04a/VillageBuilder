// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/Inventory/InventoryDragWidgetBase.h"
#include "Components/Image.h"

void UInventoryDragWidgetBase::Init(UMaterialInterface* Icon)
{
	ItemIcon->SetBrushFromMaterial(Icon);
}
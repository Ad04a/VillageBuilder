// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/Inventory/InventoryWidgetBase.h"
#include "DataTransfers/VisualizationInfos/InventoryVisualInfo.h"
#include "UI/Widgets/Gameplay/Inventory/InventoryDragWidgetBase.h"
#include "Items/StoredItemInfo.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"

void UInventoryWidgetBase::Init(UVisualizationInfo* VisualInfo)
{
	UInventoryVisualInfo* InventoryInfo = Cast<UInventoryVisualInfo>(VisualInfo);
	if (IsValid(InventoryInfo) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidgetBase::Init Provided visual info is not of class UInventoryVisualInfo"));
		return;
	}
	UCanvasPanelSlot* BorderSlot = ContentCanvas->AddChildToCanvas(GridBorder);
	BorderSlot->SetSize(InventoryInfo->GetSize() * TileSize);
	GetLinesToDraw(InventoryInfo->GetSize());
	InventoryInfo->OnItemsUpdated.BindDynamic(this, &UInventoryWidgetBase::RevieveUpdatedItems);
	InventoryInfo->InvokeInitial();
}

void UInventoryWidgetBase::RevieveUpdatedItems(TArray<UMaterialInterface*> Icons, TArray<FIntPoint> Sizes, TArray<FIntPoint> Indexes)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidgetBase::RevieveUpdatedItems IsValid(World) == false"));
		return;
	}

	ContentCanvas->ClearChildren();
	UInventoryDragWidgetBase* DragWidget = nullptr;
	for (int i=0; i< Icons.Num(); i++)
	{
		DragWidget = Cast<UInventoryDragWidgetBase>(CreateWidget<UUserWidget>(World, DragWidgetClass));
		if (IsValid(DragWidget) == false) {
			UE_LOG(LogTemp, Error, TEXT("UInventoryWidgetBase::RevieveUpdatedItems IsValid(DragWidget) == false"));
			continue;
		}
		DragWidget->Init(Icons[i]);

		UCanvasPanelSlot* ItemSlot = ContentCanvas->AddChildToCanvas(DragWidget);
		ItemSlot->SetSize(Sizes[i]*TileSize);
		ItemSlot->SetPosition(Indexes[i]*TileSize);
	}
}

void UInventoryWidgetBase::GetLinesToDraw(FVector2D Size)
{
	FLine Line;
	for (int X = 0; X <= Size.X; X++)
	{
		Line.Start = FVector2D(X* TileSize, 0);
		Line.End = FVector2D(X * TileSize, Size.Y* TileSize);
		Lines.Add(Line);
	}
	for (int Y = 0; Y <= Size.Y; Y++)
	{
		Line.Start = FVector2D(0, Y * TileSize);
		Line.End = FVector2D(Size.X * TileSize, Y * TileSize);
		Lines.Add(Line);
	}
	
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/Inventory/InventoryWidgetBase.h"
#include "DataTransfers/VisualizationInfos/InventoryVisualInfo.h"
#include "UI/Widgets/Gameplay/Inventory/InventoryDragWidgetBase.h"
#include "UI/Widgets/Gameplay/Inventory/InventorySlotWidgetBase.h"

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
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidgetBase::RevieveUpdatedItems IsValid(World) == false"));
		return;
	}
	UInventorySlotWidgetBase* SlotWidget = nullptr;
	for (int Y = 0; Y < InventoryInfo->GetSize().Y; Y++)
	{
		for (int X = 0; X < InventoryInfo->GetSize().X; X++)
		{
			SlotWidget = Cast<UInventorySlotWidgetBase>(CreateWidget<UUserWidget>(World, SlotWidgetClass));
			if (IsValid(SlotWidget) == false) {
				UE_LOG(LogTemp, Error, TEXT("UInventoryWidgetBase::RevieveUpdatedItems IsValid(SlotWidget) == false"));
				continue;
			}
			SlotWidget->OnDropStarted.BindDynamic(this, &UInventoryWidgetBase::RegisterChiledDropped);
			UCanvasPanelSlot* CanvasSlot = GridCanvas->AddChildToCanvas(SlotWidget);
			CanvasSlot->SetSize(FVector2D(TileSize, TileSize));
			CanvasSlot->SetPosition(FVector2D(X , Y)* TileSize);

		}
	}
	OnChildDraged.BindDynamic(InventoryInfo, &UInventoryVisualInfo::GetItemFromStorage);
	OnChildDropped.BindDynamic(InventoryInfo, &UInventoryVisualInfo::OnDragItemDropped);
	InventoryInfo->OnItemsUpdated.BindDynamic(this, &UInventoryWidgetBase::RecieveUpdatedItems);
	InventoryInfo->InvokeInitial();
	
}

void UInventoryWidgetBase::RecieveUpdatedItems(TArray<UMaterialInterface*> Icons, TArray<FIntPoint> Sizes, TArray<FIntPoint> Indexes)
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
		DragWidget->OnDragStarted.BindDynamic(this, &UInventoryWidgetBase::RegisterChiledDraged);
		UCanvasPanelSlot* ItemSlot = ContentCanvas->AddChildToCanvas(DragWidget);
		ItemSlot->SetSize(Sizes[i]*TileSize);
		ItemSlot->SetPosition(Indexes[i]*TileSize);
	}
}

UObject* UInventoryWidgetBase::RegisterChiledDraged(UInventoryDragWidgetBase* DragedChild)
{
	if (OnChildDraged.IsBound() == false)
	{
		return nullptr;
	}
	UObject* Item = OnChildDraged.Execute(ContentCanvas->GetChildIndex(DragedChild));
	if (IsValid(Item) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidgetBase::RegisterChiledDraged IsValid(Item) == false"));
		return nullptr;
	}
	return Item;
}

void UInventoryWidgetBase::RegisterChiledDropped(UInventorySlotWidgetBase* DropedPoint, UObject* Payload)
{
	if (OnChildDropped.IsBound() == false)
	{
		return;
	}
	OnChildDropped.Execute(Payload,GridCanvas->GetChildIndex(DropedPoint));
}

/*void UInventoryWidgetBase::GetLinesToDraw(FVector2D Size)
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
	
}*/
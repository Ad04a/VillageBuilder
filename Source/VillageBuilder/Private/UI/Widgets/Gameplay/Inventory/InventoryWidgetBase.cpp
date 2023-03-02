// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/Inventory/InventoryWidgetBase.h"
#include "DataTransfers/VisualizationInfos/InventoryVisualInfo.h"
#include "UI/Widgets/Gameplay/Inventory/InventoryDragWidgetBase.h"
#include "UI/Widgets/Gameplay/Inventory/InventorySlotWidgetBase.h"
#include "UI/Widgets/Gameplay/Inventory/InventoryDropSpaceWidgetBase.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Blueprint/DragDropOperation.h"


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

	DropSpace->OnDropStarted.BindDynamic(this, &UInventoryWidgetBase::RegisterChiledDropped);

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
	OnChildDroppedInDropSpace.BindDynamic(InventoryInfo, &UInventoryVisualInfo::DropItem);
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
		DragWidget->OnDropStarted.BindDynamic(this, &UInventoryWidgetBase::RegisterChiledDropped);
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

void UInventoryWidgetBase::RegisterChiledDropped(UWidget* DropedPoint, UObject* Payload)
{
	if (DropedPoint == DropSpace)
	{
		OnChildDroppedInDropSpace.ExecuteIfBound(Payload);
		return;
	}

	OnChildDropped.ExecuteIfBound(Payload,GridCanvas->GetChildIndex(DropedPoint));
}

bool UInventoryWidgetBase::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	OnChildDroppedInDropSpace.ExecuteIfBound(InOperation->Payload);
	return true;
}
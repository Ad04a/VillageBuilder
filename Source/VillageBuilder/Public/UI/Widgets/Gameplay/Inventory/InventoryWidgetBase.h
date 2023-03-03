// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/Widgets/Gameplay/DataLinks/VisualFragmentWidgetBase.h"
#include "Components/ScrollBox.h"
#include "InventoryWidgetBase.generated.h"


DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(UObject*, FChildDraged, int, Index, class UDragDropOperation*, InOperation);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FChildDropped, UObject*, Item, int, Index);
DECLARE_DYNAMIC_DELEGATE_OneParam(FChildDroppedInDropSpace, UObject*, Item);
DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(class UDragDropOperation*,FRotationSignature, UMaterialInterface*&, OutIcon, FIntPoint&, OutSize);

UCLASS()
class VILLAGEBUILDER_API UInventoryWidgetBase : public UVisualFragmentWidgetBase
{
	GENERATED_BODY()
private:
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* EntityName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UCanvasPanel* ContentCanvas;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UCanvasPanel* GridCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInventoryDropSpaceWidgetBase* DropSpace;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grid)
	int TileSize = 50;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventoryDragWidgetBase> DragWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventorySlotWidgetBase> SlotWidgetClass;
	
	UFUNCTION()
	void RecieveUpdatedItems(TArray<class UMaterialInterface*> Icons, TArray<FIntPoint> Sizes, TArray<FIntPoint> Indexes);

	UFUNCTION()
	UObject* RegisterChiledDraged(UInventoryDragWidgetBase* DragedChild, class UDragDropOperation* InOperation);

	UFUNCTION()
	void RegisterChiledDropped(UWidget* DropedPoint, UObject* Payload);
	
public:
	FChildDraged OnChildDraged;
	FChildDropped OnChildDropped;
	FChildDroppedInDropSpace OnChildDroppedInDropSpace;
	FRotationSignature OnRotateRequested;
	virtual void Init(class UVisualizationInfo* VisualInfo) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};

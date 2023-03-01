// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/Widgets/Gameplay/DataLinks/VisualFragmentWidgetBase.h"
#include "Components/ScrollBox.h"
#include "InventoryWidgetBase.generated.h"

USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D Start;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D End;
};

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(UObject*, FChildDraged, int, Index);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FChildDropped, UObject*, Item, int, Index);

UCLASS()
class VILLAGEBUILDER_API UInventoryWidgetBase : public UVisualFragmentWidgetBase
{
	GENERATED_BODY()
private:

	//void GetLinesToDraw(FVector2D Size);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* EntityName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UCanvasPanel* ContentCanvas;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UCanvasPanel* GridCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* DropBorder;

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grid)
	int TileSize = 50;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventoryDragWidgetBase> DragWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventorySlotWidgetBase> SlotWidgetClass;

	UFUNCTION()
	void RecieveUpdatedItems(TArray<class UMaterialInterface*> Icons, TArray<FIntPoint> Sizes, TArray<FIntPoint> Indexes);

	UFUNCTION()
	UObject* RegisterChiledDraged(UInventoryDragWidgetBase* DragedChild);

	UFUNCTION()
	void RegisterChiledDropped(UInventorySlotWidgetBase* DropedPoint, UObject* Payload);
	
public:
	FChildDraged OnChildDraged;
	FChildDropped OnChildDropped;
	virtual void Init(class UVisualizationInfo* VisualInfo) override;
};

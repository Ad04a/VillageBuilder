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

UCLASS()
class VILLAGEBUILDER_API UInventoryWidgetBase : public UVisualFragmentWidgetBase
{
	GENERATED_BODY()
private:

	void GetLinesToDraw(FVector2D Size);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* EntityName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UCanvasPanel* ContentCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* GridBorder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UCanvasPanel* GridCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grid)
	int TileSize = 50;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grid)
	FLinearColor LineColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grid)
	float LineThickness = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FLine> Lines;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventoryDragWidgetBase> DragWidgetClass;

	UFUNCTION()
	void RevieveUpdatedItems(TArray<class UMaterialInterface*> Icons, TArray<FIntPoint> Sizes, TArray<FIntPoint> Indexes);

public:
	virtual void Init(class UVisualizationInfo* VisualInfo) override;
};

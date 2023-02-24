// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryDragWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UInventoryDragWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category = DragDrop, meta = (BindWidget))
	class UImage* ItemIcon;

	UPROPERTY(EditDefaultsOnly, Category = DragDrop, meta = (BindWidget))
	class UBorder* ItemBorder;	

};

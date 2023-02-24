// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"
#include "InventoryRowWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UInventoryRowWidgetBase : public UUserWidget
{
	GENERATED_BODY()
private:
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UWrapBox* ContentWrapBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UInventorySlotWidgetBase> InventorySlotClass;
};

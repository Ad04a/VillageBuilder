// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RequestWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API URequestWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UCanvasPanel* RequestCanvas;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* VillagerName;

	UPROPERTY(EditDefaultsOnly)
	class TSubclassOf<class URequestModuleWidgetBase> RequestModuleClass;

	UPROPERTY(EditDefaultsOnly)
	int ItemOffset;

public:

	void Init(FText Villager, TMap<FString, int> Clasess, bool IsFull);
};

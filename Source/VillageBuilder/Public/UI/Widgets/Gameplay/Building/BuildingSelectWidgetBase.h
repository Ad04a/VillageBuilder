// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "BuildingSelectWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FBuildButtonClickedSignature, FString, Name);

UCLASS()
class VILLAGEBUILDER_API UBuildingSelectWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* SelectButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* BuildingNameText;

	UFUNCTION()
	void ButtonClicked();

public:
	void NativeOnInitialized() override;
	void Init(FString Name);
	FBuildButtonClickedSignature OnButtonClicked;
};

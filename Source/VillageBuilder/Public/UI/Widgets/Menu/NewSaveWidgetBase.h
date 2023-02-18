// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "NewSaveWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE(FButtonClikcedSignature);
DECLARE_DYNAMIC_DELEGATE_OneParam(FCreateClikcedSignature, FString, SaveName);

UCLASS()
class VILLAGEBUILDER_API UNewSaveWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UEditableTextBox* SaveName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* CreateButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ErrorText;

	UPROPERTY(EditAnywhere)
	int MinNameLenght;

	UPROPERTY(EditAnywhere)
	int MaxNameLenght;

	bool bCanCreate = false;

	UFUNCTION()
	void MangeEnteredText(const FText& Text);

	UFUNCTION()
	void BackClicked();

	UFUNCTION()
	void CreateClicked();

public:
	void NativeOnInitialized() override;
	void NativeConstruct() override;
	FCreateClikcedSignature OnCreateClicked;
	FButtonClikcedSignature OnBackClicked;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "UI/Widgets/Menu/GameInfoWidgetBase.h"
#include "ChooseSaveGameWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE(FButtonClickedSignature);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSaveGameChosenSignature, FString, GameSlotName);

UCLASS()
class VILLAGEBUILDER_API UChooseSaveGameWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ChooseText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UScrollBox* SaveGamesScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* CreateButton;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameInfoWidgetBase> GameInfoWidgetBaseClass;

	UFUNCTION()
	void BackClicked();

	UFUNCTION()
	void CreateClicked();

	UFUNCTION()
	void RegisterChosenSave(FString SaveName);

public:
	void Init(TArray<FString> SaveSlots);
	void NativeOnInitialized()override;
	FGameInfoButtonClicked OnSlotSelected;
	FButtonClickedSignature OnBackClicked;
	FButtonClickedSignature OnCreateClicked;
};

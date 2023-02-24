// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "BuildMenuWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FBuildingSelectedSignature, FString, BuildingName);
DECLARE_DYNAMIC_DELEGATE(FCloseSignalSignature);

UCLASS()
class VILLAGEBUILDER_API UBuildMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UScrollBox* BuildingScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UBuildingSelectWidgetBase> BuildingSelectClass;

	UFUNCTION()
	void BuildingSelected(FString SelectedBuildingName);

	UFUNCTION()
	void CloseClicked();

public:

	FBuildingSelectedSignature OnBuildingSelected;
	FCloseSignalSignature OnCloseSignal;

	void Init(TArray<FString> Buildings);
	void NativeOnInitialized() override;
};

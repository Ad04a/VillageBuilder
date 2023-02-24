// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EmployeeWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FManageButtonSignature, UEmployeeWidgetBase*, Emitter);

UCLASS()
class VILLAGEBUILDER_API UEmployeeWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTraitWidgetBase* TraitWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* ManageButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ManageButtonText;

	UFUNCTION()
	void ManageButtonCliked();

public:
	void Init();

	void NativeOnInitialized() override;

	FManageButtonSignature OnManageButtonClicked;
	
};
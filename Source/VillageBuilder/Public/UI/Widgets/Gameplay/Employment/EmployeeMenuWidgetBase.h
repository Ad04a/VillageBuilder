// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EmployeeMenuWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FEmploymentButtonSignature, int, VillagerID);

UCLASS()
class VILLAGEBUILDER_API UEmployeeMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()
private:
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* StationName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UScrollBox* VillagerScrollBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UEmployeeWidgetBase> EmployeeWidgetClass;

	UFUNCTION()
	void ManageButtonClicked(UEmployeeWidgetBase* EmitterWidget);

public:
	void Init();

	UFUNCTION()
	void LoadVillagerWidgets();

	FEmploymentButtonSignature OnVillagerEmployed;
};

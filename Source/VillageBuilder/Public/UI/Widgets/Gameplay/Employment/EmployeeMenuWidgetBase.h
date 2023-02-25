// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/Widgets/Gameplay/DataLinks/VisualFragmentWidgetBase.h"
#include "EmployeeMenuWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FEmploymentButtonSignature, int, VillagerID);

UCLASS()
class VILLAGEBUILDER_API UEmployeeMenuWidgetBase : public UVisualFragmentWidgetBase
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

	virtual void Init(class UVisualizationInfo* VisualInfo) override;

	UFUNCTION()
	void LoadVillagerWidgets();

	FEmploymentButtonSignature OnVillagerEmployed;

};

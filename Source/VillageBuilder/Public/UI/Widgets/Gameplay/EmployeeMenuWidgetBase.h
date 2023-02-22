// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "UI/Widgets/Gameplay/EmployeeWidgetBase.h"
#include "EmployeeMenuWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FEmploymentButtonSignature, ABaseWorkStation*, WorkStation, int, VillagerID);

UCLASS()
class VILLAGEBUILDER_API UEmployeeMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()
private:
	ABaseWorkStation* CurrentWorkStation = nullptr;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* StationName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UScrollBox* VillagerScrollBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEmployeeWidgetBase> EmployeeWidgetClass;

	UFUNCTION()
	void ManageButtonClicked(UEmployeeWidgetBase* EmitterWidget);

public:
	void Init(ABaseWorkStation* WorkStation);

	UFUNCTION()
	void LoadVillagerWidgets(TArray<AVillager*> Villagers);

	FEmploymentButtonSignature OnVillagerEmployed;
};

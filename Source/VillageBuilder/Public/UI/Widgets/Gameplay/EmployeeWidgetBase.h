// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Characters/Villager.h"
#include "WorkSystem/BaseWorkStation.h "
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "EmployeeWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FManageButtonSignature, AVillager*, Villagers);

UCLASS()
class VILLAGEBUILDER_API UEmployeeWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	TMap<TEnumAsByte<ETrait>, UTextBlock*> TextBlocks;
	TMap<TEnumAsByte<ETrait>, FString> TraitNames;

	AVillager* CurrentVillager = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Vitality;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Survivability;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Agility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Strength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Dexterity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* ManageButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ManageButtonText;


	void SetTrait(ETrait TraitName, int Value, FSlateColor Color);

	FSlateColor GetTraitColor(float Modifier);

	UFUNCTION()
	void ManageButtonCliked();

public:
	void Init(AVillager* Villager, ABaseWorkStation* WorkStation);

	void NativeOnInitialized() override;

	FManageButtonSignature OnManageButtonClicked;
	
};

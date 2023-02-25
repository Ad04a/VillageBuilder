// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/StatAndTraitEnums.h"
#include "TraitWidgetBase.generated.h"

UCLASS()
class VILLAGEBUILDER_API UTraitWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	TMap<TEnumAsByte<ETrait>, class UTextBlock*> Values;
	TMap<TEnumAsByte<ETrait>, class UTextBlock*> Names;

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
	class UTextBlock* VitalityValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* SurvivabilityValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* AgilityValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* StrengthValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* DexterityValue;

	void SetTrait(ETrait TraitName, int Value, FSlateColor Color);

	FSlateColor GetTraitColor(float Modifier);

public:
	void Init(FString InName, TMap<TEnumAsByte<ETrait>, float> InTraitMap, TMap<TEnumAsByte<ETrait>, float> Scaling = TMap<TEnumAsByte<ETrait>, float>());

	void NativeOnInitialized() override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Gameplay/StatsAndTraits/TraitWidgetBase.h"

#include "Styling/SlateColor.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void UTraitWidgetBase::NativeOnInitialized()
{
	Names.Add(ETrait::Vitality, Vitality);
	Names.Add(ETrait::Survivability, Survivability);
	Names.Add(ETrait::Agility, Agility);
	Names.Add(ETrait::Strength, Strength);
	Names.Add(ETrait::Dexterity, Dexterity);

	Values.Add(ETrait::Vitality, VitalityValue);
	Values.Add(ETrait::Survivability, SurvivabilityValue);
	Values.Add(ETrait::Agility, AgilityValue);
	Values.Add(ETrait::Strength, StrengthValue);
	Values.Add(ETrait::Dexterity, DexterityValue);

}

void UTraitWidgetBase::Init(FVillagerVisualInfoStruct VisualStruct, TMap<TEnumAsByte<ETrait>, float> Scaling)
{
	Name->SetText(FText::FromString(VisualStruct.Name));
	Profession->SetText(FText::FromString(VisualStruct.Profession));
	for (TPair<ETrait, int> Trait : VisualStruct.TraitMap)
	{
		float Color = 0;
		if (Scaling.Contains(Trait.Key))
		{
			Color = *Scaling.Find(Trait.Key);
		}
		SetTrait(Trait.Key, Trait.Value, GetTraitColor(Color));
	}
}

void UTraitWidgetBase::SetTrait(ETrait TraitName, int Value, FSlateColor Color)
{
	UTextBlock* NameTextBlock = *Names.Find(TraitName);
	UTextBlock* ValueTextBlock = *Values.Find(TraitName);
	if (NameTextBlock == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("UEmployeeWidgetBase::SetTrait IsValid(Trait) == false"));
		return;
	}
	if (ValueTextBlock == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("UEmployeeWidgetBase::SetTrait IsValid(Trait) == false"));
		return;
	}
	NameTextBlock->SetText(FText::FromString(UEnum::GetValueAsString(TraitName)));
	ValueTextBlock->SetText(FText::FromString(FString::FromInt(Value)));
	NameTextBlock->SetColorAndOpacity(Color);
}


FSlateColor UTraitWidgetBase::GetTraitColor(float Modifier)
{
	if (Modifier <= -1)
	{
		return FSlateColor(FLinearColor(1, 0, 0, 1.0f)); //Red
	}
	if (Modifier < 0)
	{
		return FSlateColor(FLinearColor(1, 0.23, 0, 1.0f)); //Orange
	}
	if (Modifier >= 1)
	{
		return FSlateColor(FLinearColor(0, 1, 0, 1.0f)); //Green
	}
	if (Modifier > 0)
	{
		return FSlateColor(FLinearColor(1, 1, 0, 1.0f)); //Yellow
	}
	return FSlateColor(FLinearColor(1, 1, 1, 1.0f));//White
}
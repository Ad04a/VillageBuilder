// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/Gameplay/StatsAndTraits/TraitWidgetBase.h"

#include "Styling/SlateColor.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void UTraitWidgetBase::NativeOnInitialized()
{
	TextBlocks.Add(ETrait::Vitality, Vitality);
	TextBlocks.Add(ETrait::Survivability, Survivability);
	TextBlocks.Add(ETrait::Agility, Agility);
	TextBlocks.Add(ETrait::Strength, Strength);
	TextBlocks.Add(ETrait::Dexterity, Dexterity);

	TraitNames.Add(ETrait::Vitality, FString("Vitality"));
	TraitNames.Add(ETrait::Survivability, FString("Survivability"));
	TraitNames.Add(ETrait::Agility, FString("Agility"));
	TraitNames.Add(ETrait::Strength, FString("Strength"));
	TraitNames.Add(ETrait::Dexterity, FString("Dexterity"));

}

void UTraitWidgetBase::Init(TMap<TEnumAsByte<ETrait>, int> InTraitMap, TMap<TEnumAsByte<ETrait>, float> Scaling)
{
	/*CurrentVillager = Villager;
	ManageButtonText->SetText(FText::FromString("Hire"));
	int Color = 0;
	if ((Villager->GetWorkStation() == WorkStation)) {
		CurrentVillager = nullptr;
		ManageButtonText->SetText(FText::FromString("Fire"));
		Color = -2;
	}
	ManageButtonText->SetColorAndOpacity(GetTraitColor(Color));
	Name->SetText(FText::FromString(Villager->GetName()));
	for (ETrait Trait : TEnumRange<ETrait>())
	{
		SetTrait(Trait, Villager->GetTrait(Trait), GetTraitColor(WorkStation->GetModifier(Trait)));
	}*/
}

void UTraitWidgetBase::SetTrait(ETrait TraitName, int Value, FSlateColor Color)
{
	UTextBlock* TextBlock = *TextBlocks.Find(TraitName);
	FString Text = *TraitNames.Find(TraitName);
	if (TextBlock == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("UEmployeeWidgetBase::SetTrait IsValid(Trait) == false"));
		return;
	}
	TextBlock->SetText(FText::FromString(Text + " " + FString::FromInt(Value)));
	TextBlock->SetColorAndOpacity(Color);
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
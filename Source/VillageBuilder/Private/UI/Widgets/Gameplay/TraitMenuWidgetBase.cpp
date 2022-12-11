// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/TraitMenuWidgetBase.h"

void UTraitMenuWidgetBase::SetStat(EStat StatName, float Current, float Max)
{
	UProgressBar** ProgressBar = StatMap.Find(StatName);
	if (ProgressBar == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("UTraitMenuWidgetBase::SetStat IsValid(Stat) == false, %f"), Current);
		return;
	}
	(*ProgressBar)->SetPercent(Current / Max);
}


void UTraitMenuWidgetBase::SetTrait(ETrait TraitName, int Value)
{
	UTextBlock** TextBlock = TraitMap.Find(TraitName);
	if (TextBlock == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("UTraitMenuWidgetBase::SetTrait IsValid(Trait) == false"));
		return;
	}
	(*TextBlock)->SetText(FText::FromString(FString::FromInt(Value)));
}

void UTraitMenuWidgetBase::NativeOnInitialized()
{
	StatMap.Add(EStat::Hunger, HungerBar);
	StatMap.Add(EStat::Energy, EnergyBar);
	StatMap.Add(EStat::Health, HealthBar);
	StatMap.Add(EStat::Thirst, ThirstBar);

	TraitMap.Add(ETrait::Vitality, Vitality);
	TraitMap.Add(ETrait::Survivability, Survivability);
	TraitMap.Add(ETrait::Agility, Agility);
	TraitMap.Add(ETrait::Strength, Strength);
	TraitMap.Add(ETrait::Dexterity, Dexterity);
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/StatsAndTraits/StatWidgetBase.h"
void UStatWidgetBase::NativeOnInitialized() {
	StatMap.Add(EStat::Hunger, HungerBar);
	StatMap.Add(EStat::Energy, EnergyBar);
	StatMap.Add(EStat::Health, HealthBar);
	StatMap.Add(EStat::Thirst, ThirstBar);
}

void UStatWidgetBase::Init(AVillager* Villager)
{
	Villager->OnStatUpdated.AddDynamic(this, &UStatWidgetBase::SetStat);
	Villager->AcknowledgeWidgetBinding();
}

void UStatWidgetBase::SetStat(EStat StatName, float Current, float Max)
{
	UProgressBar** ProgressBar = StatMap.Find(StatName);
	if (ProgressBar == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("UStatWidgetBase::SetStat IsValid(Stat) == false"));
		return;
	}
	(*ProgressBar)->SetPercent(Current/Max);
}




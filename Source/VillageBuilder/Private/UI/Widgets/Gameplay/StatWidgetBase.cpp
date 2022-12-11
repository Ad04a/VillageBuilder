// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/StatWidgetBase.h"

void UStatWidgetBase::SetStat(EStat StatName, float Current, float Max)
{
	UProgressBar** ProgressBar = StatMap.Find(StatName);
	if (ProgressBar == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("UStatWidgetBase::SetStat IsValid(Stat) == false"));
		return;
	}
	(*ProgressBar)->SetPercent(Current/Max);
}

void UStatWidgetBase::NativeOnInitialized() {
	StatMap.Add(EStat::Hunger, HungerBar);
	StatMap.Add(EStat::Energy, EnergyBar);
	StatMap.Add(EStat::Health, HealthBar);
	StatMap.Add(EStat::Thirst, ThirstBar);
}
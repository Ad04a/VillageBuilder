// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/StatWidgetBase.h"

void UStatWidgetBase::SetHunger(float HungerPercent)
{
	HungerBar->SetPercent(HungerPercent);
}


void UStatWidgetBase::SetThirst(float ThirstPercent)
{
	ThirstBar->SetPercent(ThirstPercent);
}


void UStatWidgetBase::SetEnergy(float EnergyPercent)
{
	EnergyBar->SetPercent(EnergyPercent);
}


void UStatWidgetBase::SetHealth(float HealthPercent)
{
	HealthBar->SetPercent(HealthPercent);
}

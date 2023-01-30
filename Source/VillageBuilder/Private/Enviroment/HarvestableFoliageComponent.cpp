// Fill out your copyright notice in the Description page of Project Settings.


#include "Enviroment/HarvestableFoliageComponent.h"

UHarvestableFoliageComponent::UHarvestableFoliageComponent()
{
	OnInstanceTakePointDamage.AddDynamic(this, &UHarvestableFoliageComponent::TakeDamage);
}

void UHarvestableFoliageComponent::TakeDamage(int32 InstanceIndex, float Damage, class AController* InstigatedBy, FVector HitLocation, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser)
{
	//this->SetCustomDataValue(InstanceIndex, 0, this->PerInstanceSMCustomData[0] - Damage);
	UE_LOG(LogTemp, Error, TEXT(" index %d Takena damage"), InstanceIndex);
		
}
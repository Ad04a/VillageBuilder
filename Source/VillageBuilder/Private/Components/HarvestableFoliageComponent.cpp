// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HarvestableFoliageComponent.h"

UHarvestableFoliageComponent::UHarvestableFoliageComponent()
{
	OnInstanceTakePointDamage.AddDynamic(this, &UHarvestableFoliageComponent::TakeDamage);
}

void UHarvestableFoliageComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < GetInstanceCount(); i++)
	{
		PerInstanceHealth.Add(InstanceBaseHealth);

	}
}

void UHarvestableFoliageComponent::TakeDamage(int32 InstanceIndex, float Damage, class AController* InstigatedBy, FVector HitLocation, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser)
{
	PerInstanceHealth[InstanceIndex] = PerInstanceHealth[InstanceIndex] - Damage;
	UE_LOG(LogTemp, Error, TEXT(" index %d Takena damage i e s health %f"), InstanceIndex, PerInstanceHealth[InstanceIndex]);
	
	if (PerInstanceHealth[InstanceIndex] > 0)
	{
		return;
	}
	FTransform InstanceTransform;
	GetInstanceTransform(InstanceIndex, InstanceTransform, true);
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UItemCarrierComponent::DropItem IsValid(World) == false"));
		return;
	}
	RemoveInstance(InstanceIndex);
	World->SpawnActor<AHarvestableActor>(HarvestableActorClass, InstanceTransform.GetLocation(), FRotator(InstanceTransform.GetRotation()));
	
		
}
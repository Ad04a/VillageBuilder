// Fill out your copyright notice in the Description page of Project Settings.


#include "Enviroment/HarvestableActor.h"

AHarvestableActor::AHarvestableActor()
{
	ItemCarrierComponent = CreateDefaultSubobject<UItemCarrierComponent>(TEXT("ItemCarriage"));
}

void AHarvestableActor::Disappear()
{
	ItemCarrierComponent->DropAllItems();
	Destroy();
}

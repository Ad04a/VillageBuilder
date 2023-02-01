// Fill out your copyright notice in the Description page of Project Settings.


#include "Enviroment/HarvestableRock.h"

AHarvestableRock::AHarvestableRock()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
}

void AHarvestableRock::BeginPlay()
{
	Super::BeginPlay();
	Disappear();
}
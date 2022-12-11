// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Items/Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::InteractRequest_Implementation(class AVillager* InteractingVillager)
{
	Use(InteractingVillager);
}

FText AItem::DisplayInteractText_Implementation()
{
	return FText::FromString( "Pick up " + DisplayName.ToString());
}


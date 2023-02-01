// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/BaseWorkStation.h"

// Sets default values
ABaseWorkStation::ABaseWorkStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
}

// Called when the game starts or when spawned
void ABaseWorkStation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWorkStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


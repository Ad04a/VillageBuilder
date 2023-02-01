// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemCarrierComponent.h"

// Sets default values for this component's properties
UItemCarrierComponent::UItemCarrierComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemCarrierComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemCarrierComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UItemCarrierComponent::DropItem(TSubclassOf<AItem> ItemClass)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UItemCarrierComponent::DropItem IsValid(World) == false"));
		return;
	}
	AActor* Owner = GetOwner();
	if (IsValid(Owner) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UItemCarrierComponent::DropItem IsValid(Owner) == false"));
		return;
	}
	FVector  SpawnLocation = Owner->GetActorLocation();
	FRotator SpawnRotation = Owner->GetActorRotation();
	World->SpawnActor<AItem>(ItemClass, SpawnLocation, SpawnRotation);
}

void UItemCarrierComponent::DropAllItems()
{
	for (TPair<TSubclassOf<AItem>,int> ItemType : Content)
	{
		for (int i = 0; i < ItemType.Value; i++) {
			DropItem(ItemType.Key);
		}
	}
}


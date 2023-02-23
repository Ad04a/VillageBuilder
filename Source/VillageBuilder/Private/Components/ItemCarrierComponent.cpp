// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemCarrierComponent.h"

// Sets default values for this component's properties
UItemCarrierComponent::UItemCarrierComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UItemCarrierComponent::AddItem(AItem* Item)
{
	TSubclassOf<AItem> ItemClass = Item->GetClass();
	if (Content.Contains(ItemClass) == true)
	{
		Content.Add(ItemClass, *Content.Find(ItemClass) + 1);
		return;
	}
	Content.Add(ItemClass, 1);
}

AItem* UItemCarrierComponent::DropItem(TSubclassOf<AItem> ItemClass)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UItemCarrierComponent::DropItem IsValid(World) == false"));
		return nullptr;
	}
	AActor* Owner = GetOwner();
	if (IsValid(Owner) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UItemCarrierComponent::DropItem IsValid(Owner) == false"));
		return nullptr;
	}
	FVector  SpawnLocation = Owner->GetActorLocation();
	FRotator SpawnRotation = Owner->GetActorRotation();
	if (Content.Contains(ItemClass) == false)
	{
		return nullptr;
	}
	Content.Emplace(ItemClass, *Content.Find(ItemClass)-1);
	if (*Content.Find(ItemClass) <= 0)
	{
		Content.FindAndRemoveChecked(ItemClass);
	}
	return World->SpawnActor<AItem>(ItemClass, SpawnLocation, SpawnRotation);
}

void UItemCarrierComponent::DropAllItems()
{
	TArray<TSubclassOf<AItem>> ArrayOfClasses;
	Content.GenerateKeyArray(ArrayOfClasses);
	for (TSubclassOf<AItem> ItemType : ArrayOfClasses)
	{
		int Times = *Content.Find(ItemType);
		for (int i = 0; i < Times; i++) {
			DropItem(ItemType);
		}
	}
}

TArray<TSubclassOf<AItem>> UItemCarrierComponent::GetItemTypes()
{
	TArray<TSubclassOf<AItem>> TempArray;
	Content.GenerateKeyArray(TempArray);
	return TempArray;
}


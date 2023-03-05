// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseBuildingComponent.h"
#include "Characters/Villager.h"
#include "Engine/StaticMeshActor.h"

UBaseBuildingComponent::UBaseBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBaseBuildingComponent::InteractRequest_Implementation(class AVillager* InteractingVillager)
{
	if (bIsActive == false)
	{
		return;
	}
	AItem* UsingItem = InteractingVillager->GetItem();
	if (IsValid(UsingItem) == false)
	{
		return;
	}
	if (UsingItem->IsA(NeededItem) == false)
	{
		return;
	}

	InteractingVillager->DropItem()->Destroy();
	//UsingItem->Destroy();
	Build();
}

void UBaseBuildingComponent::Build()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBaseBuildingComponent::Build IsValid(World) == false"));
		return;
	}

	bIsPlaced = true;
	
	OnComponentStateChange.ExecuteIfBound(ID,true);
	FActorSpawnParameters SpawnParams;
	AStaticMeshActor* NewMesh = World->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), GetComponentLocation(), GetComponentRotation(), SpawnParams);
	NewMesh->SetMobility(EComponentMobility::Movable);
	NewMesh->GetStaticMeshComponent()->SetStaticMesh(GetStaticMesh());
	NewMesh->GetStaticMeshComponent()->SetMaterial(0, PlacedMaterial);
	NewMesh->SetMobility(EComponentMobility::Static);
	DestroyComponent();
}

void UBaseBuildingComponent::SetIsActive(bool State)
{
	SetVisibility(State);
	bIsActive = State;
	if (State == false)
	{
		SetCollisionProfileName(TEXT("OverlapAll"));
		SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
		return;
	}
	SetCollisionProfileName(TEXT("Custom"));
	SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
}

FText UBaseBuildingComponent::DisplayInteractText_Implementation()
{
	return InteractionText;
}
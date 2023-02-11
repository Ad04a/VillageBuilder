// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BaseBuildingComponent.h"

UBaseBuildingComponent::UBaseBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	OnComponentBeginOverlap.AddDynamic(this, &UBaseBuildingComponent::Touched);
}


void UBaseBuildingComponent::Touched(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(NeededItem) == false || bIsPlaced == true || bIsActive == false) {
		return;
	}

	AItem* TouchingItem = Cast<AItem>(OtherActor);
	
	SetMaterial(0, TouchingItem->GetMaterial());
	bIsPlaced = true;
	SetCollisionProfileName(TEXT("BlockAll"));
	TouchingItem->Destroy();
	OnComponentStateChange.ExecuteIfBound(true);
	UStaticMeshComponent* NewMesh = NewObject<UStaticMeshComponent>(GetAttachParent());
	NewMesh->RegisterComponent();
	NewMesh->AttachToComponent(GetAttachParent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	NewMesh->SetStaticMesh(GetStaticMesh());
	NewMesh->SetRelativeLocationAndRotation(GetRelativeLocation(),GetRelativeRotation());
	DestroyComponent();
}

void UBaseBuildingComponent::SetIsActive(bool State)
{
	SetVisibility(State);
	bIsActive = State;
}
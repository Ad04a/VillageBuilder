// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BuildingClusterComponent.h"
#include "Components/BaseBuildingComponent.h"

void UBuildingClusterComponent::BeginPlay()
{
	Super::BeginPlay();
	TArray<USceneComponent*>Children;
	GetChildrenComponents(true,Children);
	for (USceneComponent* Child : Children)
	{
		UE_LOG(LogTemp, Warning, TEXT("Component: %s"), *Child->GetName());
		UBaseBuildingComponent* BuildingComp = Cast<UBaseBuildingComponent>(Child);
		if (IsValid(BuildingComp) == false) {
			continue;
		}
		BuildingComp->SetMaterial(0, MainMaterial);
	}
}

void UBuildingClusterComponent::InteractRequest_Implementation(class AVillageMayor* InteractingPlayer)
{
	return;
}

FText UBuildingClusterComponent::DisplayInteractText_Implementation()
{
	return FText::FromString("0 / 15");
}
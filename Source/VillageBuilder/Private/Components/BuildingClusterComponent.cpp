// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BuildingClusterComponent.h"
#include "Components/BaseBuildingComponent.h"

void UBuildingClusterComponent::BeginPlay()
{
	Super::BeginPlay();
	TArray<USceneComponent*>Children;
	GetChildrenComponents(false,Children);
	for (USceneComponent* Child : Children)
	{
		UBaseBuildingComponent* BuildingComp = Cast<UBaseBuildingComponent>(Child);
		if (IsValid(Child) == false) {
			continue;
		}
		BuildingComp->SetMaterial(0, MainMaterial);
	}
}

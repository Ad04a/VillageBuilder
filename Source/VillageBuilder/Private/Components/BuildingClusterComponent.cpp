// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BuildingClusterComponent.h"
#include "Components/BaseBuildingComponent.h"

void UBuildingClusterComponent::BeginPlay()
{
	Super::BeginPlay();
	for (UBaseBuildingComponent* Child : GetBuildingComponents())
	{
		Child->SetMaterial(0, MainMaterial);
		Child->OnComponentStateChange.BindDynamic(this, &UBuildingClusterComponent::OnComponentPlaced);
		Child->SetIsActive(false);
		AllComponents++;
	}
}

void UBuildingClusterComponent::InteractRequest_Implementation(class AVillager* InteractingVillager)
{
	if (bIsStarted == true)
	{
		OnBuildStarted.ExecuteIfBound(true);
		return;
	}
	bIsStarted = true;
	for (UBaseBuildingComponent* Child : GetBuildingComponents())
	{
		Child->SetIsActive(true);
	}
}

FText UBuildingClusterComponent::DisplayInteractText_Implementation()
{
	if (bIsStarted == false)
	{
		return FText::FromString("Start building");
	}
	return FText::FromString(FString::FromInt(PlacedComponents) + " / " + FString::FromInt(AllComponents));
}

void UBuildingClusterComponent::OnComponentPlaced(bool State)
{
	if (State == false)
	{
		PlacedComponents--;
		return;
	}
	PlacedComponents++;
	if (PlacedComponents == AllComponents)
	{
		OnBuildingFinisehd.ExecuteIfBound(true);
	}
}

TArray<class UBaseBuildingComponent*> UBuildingClusterComponent::GetBuildingComponents()
{
	TArray<USceneComponent*>Children;
	GetChildrenComponents(true, Children);
	TArray<UBaseBuildingComponent*> BuildingComponents;
	for (USceneComponent* Child : Children)
	{
		UBaseBuildingComponent* BuildingComp = Cast<UBaseBuildingComponent>(Child);
		if (IsValid(BuildingComp) == false) {
			continue;
		}
		BuildingComponents.Add(BuildingComp);
	}
	return BuildingComponents;
}
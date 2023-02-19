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
		Child->ID = AllComponents;
		AllComponents++;
	}
}

void UBuildingClusterComponent::Init(FBuildingClusterInfoStruct InLoadInfo)
{
	if (InLoadInfo == FBuildingClusterInfoStruct())
	{
		return;
	}
	if (InLoadInfo.bIsConstructing == true)
	{
		bIsStarted = InLoadInfo.bIsConstructing;
		OnBuildStarted.ExecuteIfBound(bIsStarted);
	}
	PlacedIDs = InLoadInfo.PlacedIDs;
	for (UBaseBuildingComponent* Child : GetBuildingComponents())
	{
		Child->SetIsActive(bIsStarted);
		if (InLoadInfo.PlacedIDs.Contains(Child->ID) == true)
		{
			Child->Build();
		}
	}
}

FBuildingClusterInfoStruct UBuildingClusterComponent::GetSaveInfo()
{
	FBuildingClusterInfoStruct SaveInfo;
	SaveInfo.PlacedIDs = PlacedIDs;
	SaveInfo.bIsConstructing = bIsStarted;
	return SaveInfo;
}

void UBuildingClusterComponent::InteractRequest_Implementation(class AVillager* InteractingVillager)
{
	if (bIsStarted == true)
	{
		return;
	}
	bIsStarted = true;
	OnBuildStarted.ExecuteIfBound(true);
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
	if (PlacedComponents == AllComponents)
	{
		return FText::FromString("Repair: " + FString::FromInt(PlacedComponents) + " / " + FString::FromInt(AllComponents));
	}
	return FText::FromString("Building: " + FString::FromInt(PlacedComponents) + " / " + FString::FromInt(AllComponents));
}

void UBuildingClusterComponent::OnComponentPlaced(int ID, bool State)
{
	if (State == false)
	{
		PlacedComponents--;
		PlacedIDs.Remove(ID);
		return;
	}
	PlacedComponents++;
	PlacedIDs.Add(ID);
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

class UBaseBuildingComponent* UBuildingClusterComponent::GetFirstBuildingComponent()
{
	TArray<UBaseBuildingComponent*> BuildingComponents = GetBuildingComponents();
	if (BuildingComponents.IsEmpty() == true)
	{
		return nullptr;
	}
	return BuildingComponents[0];
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BuildingClusterComponent.h"
#include "Components/BaseBuildingComponent.h"

void UBuildingClusterComponent::BeginPlay()
{
	Super::BeginPlay();
	for (UBaseBuildingComponent* Child : GetBuildingComponents())
	{
		Child->SetMaterial(0, MainMaterial);
		Child->OnComponentStateChange.BindDynamic(this, &UBuildingClusterComponent::ComponentPlaced);
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
		OnBuildStarted.Broadcast(bIsStarted);
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
void UBuildingClusterComponent::StartBuild()
{
	bIsStarted = !bIsStarted;
	OnBuildStarted.Broadcast(bIsStarted);
	for (UBaseBuildingComponent* Child : GetBuildingComponents())
	{
		Child->SetIsActive(bIsStarted);
	}
}

void UBuildingClusterComponent::ComponentPlaced(int ID, bool State)
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
		OnBuildingFinisehd.Broadcast(true);
	}
	OnComponentPlaced.Broadcast(GetBuildingComponents());
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

//---------------------CheatSection-----------------------------------
void UBuildingClusterComponent::ForceBuild()
{
	for (UBaseBuildingComponent* Child : GetBuildingComponents())
	{
		Child->Build();	
	}
}
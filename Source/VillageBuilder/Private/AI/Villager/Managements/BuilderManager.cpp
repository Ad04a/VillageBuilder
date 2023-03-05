// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Managements/BuilderManager.h"
#include "Components/BuildingClusterComponent.h"
#include "Components/BaseBuildingComponent.h"
#include "WorkSystem/BaseWorkStation.h"
#include "WorkSystem/VillageManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

bool UBuilderManager::CheckGivenKeys()
{
	if (GivenKeys.Num() != 2)
	{
		UE_LOG(LogTemp, Error, TEXT("UBuilderManager::CheckGivenKeys Not given enough keys"));
		return false;
	}
	if (GivenKeys[0].SelectedKeyType == UBlackboardKeyType_Bool::StaticClass())
	{
		UE_LOG(LogTemp, Error, TEXT("UBuilderManager::CheckGivenKeys First key is not of type Bool"));
		return false;
	}
	if (GivenKeys[1].SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		UE_LOG(LogTemp, Error, TEXT("UBuilderManager::CheckGivenKeys Second key is not of type Object"));
		return false;
	}
	return true;
}

void UBuilderManager::SetTargetBuildingCluster()
{

	ABaseWorkStation* TargetWorkStationActor = Village->GetFirstForConstructing();
	if (IsValid(TargetWorkStationActor) == false)
	{
		BlackBoard->ClearValue(GivenKeys[0].SelectedKeyName);
		BlackBoard->ClearValue(GivenKeys[1].SelectedKeyName);
		return ;
	}
	TargetBuildingCluster = TargetWorkStationActor->GetBuildingComponent();
	if (IsValid(TargetBuildingCluster) == false)
	{
		BlackBoard->ClearValue(GivenKeys[0].SelectedKeyName);
		BlackBoard->ClearValue(GivenKeys[1].SelectedKeyName);
		return;
	}
	TargetBuildingCluster->OnBuildingFinisehd.AddUniqueDynamic(this, &UBuilderManager::ResetBuildingCluster);
	TargetBuildingCluster->OnBuildStarted.AddUniqueDynamic(this, &UBuilderManager::ResetBuildingCluster);
	BlackBoard->SetValueAsBool(GivenKeys[0].SelectedKeyName, true);
	BlackBoard->SetValueAsObject(GivenKeys[1].SelectedKeyName, TargetWorkStationActor);
	
}

void UBuilderManager::ResetBuildingCluster(bool State)
{
	TargetBuildingCluster->OnBuildingFinisehd.RemoveAll(this);
	TargetBuildingCluster->OnBuildStarted.RemoveAll(this);
	BlackBoard->ClearValue(GivenKeys[0].SelectedKeyName);
	BlackBoard->ClearValue(GivenKeys[1].SelectedKeyName);
	TargetBuildingCluster = nullptr;
	UpdateNeededClasses();
}

TMap<UBaseBuildingComponent*, TSubclassOf<AItem>> UBuilderManager::UpdateNeededClasses()
{
	TMap<UBaseBuildingComponent*, TSubclassOf<AItem>>  ComponentClasses;
	TArray<TSubclassOf<class AItem>> ItemClasses;

	if (TargetBuildingCluster == nullptr)
	{
		return ComponentClasses;
	}
	for (UBaseBuildingComponent* BuildComp : TargetBuildingCluster->GetBuildingComponents())
	{
		ComponentClasses.Add(BuildComp, BuildComp->GetNeededClass());
		NededItemClasses.Add(BuildComp->GetNeededClass());
	}
	return ComponentClasses;
}
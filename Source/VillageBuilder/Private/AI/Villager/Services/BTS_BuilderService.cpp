// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Services/BTS_BuilderService.h"
#include "Components/BuildingClusterComponent.h"
#include "Components/BaseBuildingComponent.h"
#include "WorkSystem/VillageManager.h"
#include "WorkSystem/BaseWorkStation.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTS_BuilderService::UBTS_BuilderService()
{
	NodeName = "BuilderService";
}

void UBTS_BuilderService::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComponent, NodeMemory);

}

void UBTS_BuilderService::SetTargetBuildingCluster()
{

	ABaseWorkStation* TargetWorkStationActor = Village->GetFirstForConstructing();
	if (IsValid(TargetWorkStationActor) == false)
	{
		BlackBoard->ClearValue(TargetWorkStation.SelectedKeyName);
		BlackBoard->ClearValue(HasWorkCheck.SelectedKeyName);
		return ;
	}
	TargetBuildingCluster = TargetWorkStationActor->GetBuildingComponent();
	if (IsValid(TargetBuildingCluster) == false)
	{
		BlackBoard->ClearValue(TargetWorkStation.SelectedKeyName);
		BlackBoard->ClearValue(HasWorkCheck.SelectedKeyName);
		return;
	}
	TargetBuildingCluster->OnBuildingFinisehd.AddUniqueDynamic(this, &UBTS_BuilderService::ResetBuildingCluster);
	TargetBuildingCluster->OnBuildStarted.AddUniqueDynamic(this, &UBTS_BuilderService::ResetBuildingCluster);
	BlackBoard->SetValueAsObject(TargetWorkStation.SelectedKeyName, TargetWorkStationActor);
	BlackBoard->SetValueAsBool(HasWorkCheck.SelectedKeyName, true);
}

void UBTS_BuilderService::ResetBuildingCluster(bool State)
{
	TargetBuildingCluster->OnBuildingFinisehd.RemoveAll(this);
	TargetBuildingCluster->OnBuildStarted.RemoveAll(this);
	BlackBoard->ClearValue(HasWorkCheck.SelectedKeyName);
	TargetBuildingCluster = nullptr;
	UpdateNeededClasses();
}

TMap<UBaseBuildingComponent*, TSubclassOf<AItem>> UBTS_BuilderService::UpdateNeededClasses()
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
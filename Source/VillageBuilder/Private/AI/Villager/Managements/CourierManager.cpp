// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Managements/CourierManager.h"
#include "headers/Request.h"
#include "WorkSystem/VillageManager.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

bool UCourierManager::CheckGivenKeys()
{
	if (GivenKeys.Num() != 1)
	{
		UE_LOG(LogTemp, Error, TEXT("UBuilderManager::CheckGivenKeys Number of needed keys is 1 but %d were given"), GivenKeys.Num());
		return false;
	}
	if (GivenKeys[0].SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		UE_LOG(LogTemp, Error, TEXT("UBuilderManager::CheckGivenKeys First key is not of type Object"));
		return false;
	}
	return true;
}

void UCourierManager::GetFirstRequest()
{
	FRequest Request =  Village->GetFirstRequest();
	if (Request.Items.IsEmpty() == true)
	{
		BlackBoard->ClearValue(GivenKeys[0].SelectedKeyName);
		NededItemClasses.Empty();
		return;
	}

	NededItemClasses = Request.Items;
	BlackBoard->SetValueAsObject(GivenKeys[0].SelectedKeyName, Request.WorkStation);
}

void UCourierManager::GetStationToClear()
{
	TArray<ABaseWorkStation*> Stations = Village->GetWorkStations();
	ABaseWorkStation* TargetWorkStation = nullptr;
	TArray<int> Indexes;
	for (int i = 0; i < Stations.Num(); i++)
	{
		Indexes.Add(i);
	}
	int i = Indexes[FMath::RandRange(0, Indexes.Num() - 1)];
	TargetWorkStation = Stations[i];
	for (; TargetWorkStation->GetClass()->GetName().Contains("Warehouse");)
	{
		Indexes.Remove(i);
		i = Indexes[FMath::RandRange(0, Indexes.Num() - 1)];
		TargetWorkStation = Stations[i];
	}

	BlackBoard->SetValueAsObject(GivenKeys[0].SelectedKeyName, TargetWorkStation);
}

void UCourierManager::Clear(AVillager* InVillager)
{
	Super::Clear(InVillager);
}
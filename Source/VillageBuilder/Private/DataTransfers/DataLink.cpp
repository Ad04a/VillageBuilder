// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/DataLink.h"
#include "DataTransfers/VisualizationInfos/StatsAndTraitsVisualInfo.h"
#include "DataTransfers/VisualizationInfos/InventoryVisualInfo.h"
#include "DataTransfers/VisualizationInfos/EmploymentVisualInfo.h"
#include "GameModes/GameplayModeBase.h"
#include "Characters/VillageMayor.h"
#include "WorkSystem/BaseWorkStation.h"
#include "Headers/DataLinkable.h"


TMap<TEnumAsByte<EVisualiationTypes>, TSubclassOf<class UVisualizationInfo>> UDataLink::TypesMap  = TMap<TEnumAsByte<EVisualiationTypes>, TSubclassOf<class UVisualizationInfo>>();

void UDataLink::InitRelations()
{
	if (UDataLink::TypesMap.IsEmpty() == false)
	{
		return;
	}
	UDataLink::TypesMap.Add(EVisualiationTypes::StatAndTrait, UStatsAndTraitsVisualInfo::StaticClass());
	UDataLink::TypesMap.Add(EVisualiationTypes::Inventory, UInventoryVisualInfo::StaticClass());
	UDataLink::TypesMap.Add(EVisualiationTypes::Employment, UEmploymentVisualInfo::StaticClass());
}

UDataLink* UDataLink::CreateDataLink(AActor* InInitiator, AActor* InTarget, EDataLinkType InLinkType)
{
	UDataLink::InitRelations();
	UDataLink* DataLink = NewObject<UDataLink>();
	if (IsValid(DataLink) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UDataLink::CreateDataLink for %s and %s: IsValid(DataLink) == false "), *InInitiator->GetName(), *InTarget->GetName());
		return nullptr;
	}
	DataLink->Initiator = InInitiator;
	DataLink->Target	= InTarget;
	DataLink->LinkType = InLinkType;
	if (DataLink->EstablishConnection() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataLink::CreateDataLink for %s and %s:\n No establishment method found for link type %s\n with Classes: %s and %s "),
										*InInitiator->GetName(), *InTarget->GetName(), *UEnum::GetValueAsString(DataLink->LinkType),
										*(DataLink->Initiator->GetClass()->GetName()), *(DataLink->Target->GetClass()->GetName()));
		return nullptr;
	}
	return DataLink;
}

bool UDataLink::EstablishConnection()
{
	if (LinkType == EDataLinkType::PlayerSelf && Initiator->IsA(AVillageMayor::StaticClass()) == true && Target == nullptr)
	{
		return true;
	}

	if (LinkType == EDataLinkType::PlayerVillager && Initiator->IsA(AVillageMayor::StaticClass()) == true && Target->IsA(AVillager::StaticClass()) == true)
	{
		return true;
	}

	if (LinkType == EDataLinkType::PlayerStation && Initiator->IsA(AVillageMayor::StaticClass()) == true && Target->IsA(ABaseWorkStation::StaticClass()) == true)
	{
		return true;
	}

	if (LinkType == EDataLinkType::VillagerStation && Initiator->IsA(AVillager::StaticClass()) == true && Target->IsA(ABaseWorkStation::StaticClass()) == true)
	{
		return true;
	}

	return false;
}

void UDataLink::BreakConnection()
{
	if (LinkType == EDataLinkType::PlayerSelf )
	{
		
	}

	if (LinkType == EDataLinkType::PlayerVillager )
	{
		
	}

	if (LinkType == EDataLinkType::PlayerStation )
	{
		
	}

	if (LinkType == EDataLinkType::VillagerStation )
	{
		
	}
	Initiator		= nullptr;
	Target			= nullptr;
	InitiatorClass  = nullptr;
	TargetClass		= nullptr;
	OnLinkBroken.ExecuteIfBound(this);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/DataLink.h"
#include "DataTransfers/VisualizationInfos/StatsAndTraitsVisualInfo.h"
#include "DataTransfers/VisualizationInfos/InventoryVisualInfo.h"
#include "DataTransfers/VisualizationInfos/EmploymentVisualInfo.h"
#include "DataTransfers/VisualizationInfos/OptionsVisualInfo.h"
#include "DataTransfers/VisualizationInfos/BuildingVisualInfo.h"
#include "DataTransfers/VisualizationInfos/ConstructionVisualInfo.h"

#include "GameModes/GameplayModeBase.h"
#include "Characters/VillageMayor.h"
#include "WorkSystem/BaseWorkStation.h"
#include "Items/BuilderItem.h"
#include "Headers/DataLinkable.h"

#include "Kismet/GameplayStatics.h"


UDataLink* UDataLink::CreateDataLink(AActor* InInitiator, AActor* InTarget)
{
	UDataLink* DataLink = NewObject<UDataLink>();
	if (IsValid(DataLink) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UDataLink::CreateDataLink IsValid(DataLink) == false "));
		return nullptr;
	}
	DataLink->Initiator = InInitiator;
	DataLink->Target	= InTarget;
	if (DataLink->EstablishConnection() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataLink::CreateDataLink No establishment method found"));
		return nullptr;
	}

	UWorld* World = InInitiator->GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UDataLink::CreateDataLink IsValid(World) == false"));
		return nullptr;
	}

	AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("UDataLink::CreateDataLink IsValid(GameMode) == false"));
		return nullptr;
	}
	GameMode->LockDataLink(DataLink);
	return DataLink;
}

bool UDataLink::EstablishConnection()
{
	if (Initiator->IsA(AVillageMayor::StaticClass()) == true && Target == nullptr)
	{
		LinkType = EDataLinkType::PlayerSelf;
		TargetInfo.Add(EVisualiationTypes::StatAndTrait, UStatsAndTraitsVisualInfo::CreateVisualInfo(Initiator));
		TargetInfo.Add(EVisualiationTypes::Inventory, UInventoryVisualInfo::CreateVisualInfo(Initiator));
		TargetInfo.Add(EVisualiationTypes::Options, UOptionsVisualInfo::CreateVisualInfo(Initiator));

		AVillager* Player = Cast<AVillager>(Initiator);
		Player->OnLinkBroken.AddDynamic(this, &UDataLink::BreakConnection);
		bShouldVisualize = true;
		return true;
	}

	if ( Initiator->IsA(AVillageMayor::StaticClass()) == true && Target->IsA(AVillager::StaticClass()) == true)
	{
		LinkType = EDataLinkType::PlayerVillager;

		InitiatorInfo.Add(EVisualiationTypes::Inventory, UInventoryVisualInfo::CreateVisualInfo(Initiator));
		AVillager* Player = Cast<AVillager>(Initiator);
		Player->OnLinkBroken.AddDynamic(this, &UDataLink::BreakConnection);

		TargetInfo.Add(EVisualiationTypes::StatAndTrait, UStatsAndTraitsVisualInfo::CreateVisualInfo(Target));
		TargetInfo.Add(EVisualiationTypes::Inventory, UInventoryVisualInfo::CreateVisualInfo(Target));
		AVillager* Villager = Cast<AVillager>(Target);
		Villager->OnLinkBroken.AddDynamic(this, &UDataLink::BreakConnection);

		bShouldVisualize = true;
		return true;
	}

	if (Initiator->IsA(AVillageMayor::StaticClass()) == true && Target->IsA(ABaseWorkStation::StaticClass()) == true)
	{
		LinkType = EDataLinkType::PlayerStation;

		AVillager* Player = Cast<AVillager>(Initiator);
		Player->OnLinkBroken.AddDynamic(this, &UDataLink::BreakConnection);
		
		ABaseWorkStation* WorkStation = Cast<ABaseWorkStation>(Target);
		WorkStation->OnLinkBroken.AddDynamic(this, &UDataLink::BreakConnection);
		if (WorkStation->GetIsBuilt() == false)
		{
			TargetInfo.Add(EVisualiationTypes::Construction, UConstructionVisualInfo::CreateVisualInfo(Target));
		}
		else
		{
			InitiatorInfo.Add(EVisualiationTypes::Inventory, UInventoryVisualInfo::CreateVisualInfo(Initiator));
			TargetInfo.Add(EVisualiationTypes::Employment, UEmploymentVisualInfo::CreateVisualInfo(Target));
			TargetInfo.Add(EVisualiationTypes::Inventory, UInventoryVisualInfo::CreateVisualInfo(Target));
		}

		bShouldVisualize = true;
		return true;
	}

	if (Initiator->IsA(AVillageMayor::StaticClass()) == true && Target->IsA(ABuilderItem::StaticClass()) == true)
	{
		LinkType = EDataLinkType::PlayerBuildTool;

		AVillager* Player = Cast<AVillager>(Initiator);
		Player->OnLinkBroken.AddDynamic(this, &UDataLink::BreakConnection);

		TargetInfo.Add(EVisualiationTypes::Building, UBuildingVisualInfo::CreateVisualInfo(Target));

		bShouldVisualize = true;
		return true;
	}

	if (Initiator->IsA(AVillager::StaticClass()) == true && Target->IsA(ABaseWorkStation::StaticClass()) == true)
	{
		LinkType = EDataLinkType::VillagerStation;
		bShouldVisualize = false;
		return true;
	}

	return false;
}

void UDataLink::BreakConnection()
{
	if (bStartedBreak == true)
	{
		return;
	}
	bStartedBreak = true;
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
	for(TPair<TEnumAsByte<EVisualiationTypes>, UVisualizationInfo*> Info : InitiatorInfo)
	{
		Info.Value->Clear();
	}
	for(TPair<TEnumAsByte<EVisualiationTypes>, UVisualizationInfo*> Info : TargetInfo)
	{
		Info.Value->Clear();
	}
	IDataLinkable* DataInitiator = Cast<IDataLinkable>(Initiator);
	if (DataInitiator != nullptr)
	{
		DataInitiator->Execute_BreakDataLinks(Initiator);
	}
	IDataLinkable* DataTarget = Cast<IDataLinkable>(Target);
	if (DataTarget != nullptr)
	{
		DataTarget->Execute_BreakDataLinks(Target);
	}
	Initiator = nullptr;
	Target 	  = nullptr;
	InitiatorInfo.Empty();
	TargetInfo.Empty();
	OnLinkBroken.Broadcast(this);
	ConditionalBeginDestroy();
}

IDataLinkable* UDataLink::GetInitiator()
{
	IDataLinkable* CastObject = Cast<IDataLinkable>(Initiator);
	if (CastObject == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT(" UDataLink::GetInitiator Initiator is not DataLinkable"));
	}
	return CastObject;
}

IDataLinkable* UDataLink::GetTarget()
{
	IDataLinkable* CastObject = Cast<IDataLinkable>(Target);
	if (CastObject == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT(" UDataLink::GetInitiator Target is not DataLinkable"));
	}
	return CastObject;
}
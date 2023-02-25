// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/StatsAndTraitsVisualInfo.h"
#include "Characters/Villager.h"

UVisualizationInfo* UStatsAndTraitsVisualInfo::CreateVisualInfo(AActor* InActor)
{
	UStatsAndTraitsVisualInfo* Info = NewObject<UStatsAndTraitsVisualInfo>();
	if (IsValid(Info) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UStatsAndTraitsVisualInfo::CreateVisualInfo Cannot create info for %s of class %s"), *InActor->GetName(), *InActor->GetClass()->GetName());
		return nullptr;
	}

	AVillager* Villager = Cast<AVillager>(InActor);
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UStatsAndTraitsVisualInfo::CreateVisualInfo Provided Actor is not of class AVillager"));
		return nullptr;
	}
	Info->Name = Villager->GetName();
	Info->LinkedVillager = Villager;
	for (ETrait Trait : TEnumRange<ETrait>())
	{
		Info->TraitMap.Add(Trait, Villager->GetTrait(Trait));
	};
	Info->LinkedVillager->OnStatUpdated.AddDynamic(Info, &UStatsAndTraitsVisualInfo::PassStatUpdate);
	return Info;
}

void UStatsAndTraitsVisualInfo::PassStatUpdate(EStat StatName, float Current, float Max)
{
	OnStatUpdated.ExecuteIfBound(StatName, Current, Max);
}

void UStatsAndTraitsVisualInfo::NotifyLinked()
{
	LinkedVillager->AcknowledgeWidgetBinding(); 
}

void UStatsAndTraitsVisualInfo::Clear()
{
	LinkedVillager->OnStatUpdated.RemoveDynamic(this, &UStatsAndTraitsVisualInfo::PassStatUpdate);
	OnStatUpdated.Unbind();
	LinkedVillager = nullptr;
}
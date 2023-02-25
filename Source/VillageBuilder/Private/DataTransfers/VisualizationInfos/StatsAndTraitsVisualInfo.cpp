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
	for (ETrait Trait : TEnumRange<ETrait>())
	{
		Info->TraitMap.Add(Trait, Villager->GetTrait(Trait));
	};
	TMap<TEnumAsByte<ETrait>, float> Scaling;
	//Villager->OnStatUpdated.AddDynamic(this, &UTraitMenuWidgetBase::SetStat);
	//Villager->AcknowledgeWidgetBinding();

	return Info;
}
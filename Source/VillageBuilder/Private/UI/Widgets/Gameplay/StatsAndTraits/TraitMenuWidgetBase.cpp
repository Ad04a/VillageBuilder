// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/StatsAndTraits/TraitMenuWidgetBase.h"
#include "UI/Widgets/Gameplay/StatsAndTraits/StatWidgetBase.h"
#include "UI/Widgets/Gameplay/StatsAndTraits/TraitWidgetBase.h"
#include "DataTransfers/VisualizationInfos/StatsAndTraitsVisualInfo.h"

void UTraitMenuWidgetBase::Init(UVisualizationInfo* VisualInfo)
{
	UStatsAndTraitsVisualInfo* StatAndTraitInfo = Cast<UStatsAndTraitsVisualInfo>(VisualInfo);
	if (IsValid(StatAndTraitInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTraitMenuWidgetBase::Init Given VisualInfo doesnt mach the required type"));
	}
	TraitWidget->Init(StatAndTraitInfo->Name, StatAndTraitInfo->TraitMap);
	StatAndTraitInfo->OnStatUpdated.BindDynamic(StatWidget, &UStatWidgetBase::SetStat);
	StatAndTraitInfo->NotifyLinked();
}



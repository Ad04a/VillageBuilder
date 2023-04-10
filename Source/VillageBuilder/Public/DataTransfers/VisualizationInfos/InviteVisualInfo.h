// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTransfers/VisualizationInfo.h"
#include "InviteVisualInfo.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UInviteVisualInfo : public UVisualizationInfo
{
	GENERATED_BODY()
protected:
	class AVillageManager* Village;
	class AVillager* Villager;
public:

	void SetInviter(class AVillageMayor* InInviter);

	UFUNCTION()
	void InviteVillager();

	static UVisualizationInfo* CreateVisualInfo(AActor* InActor);
	virtual void Clear() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Headers/VisualizationTypes.h"
#include "Headers/DataLinkable.h"
#include "DataLink.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLinkBrokenSignature, UDataLink*, BrokenLink);

UENUM(BlueprintType)
enum EDataLinkType {
	PlayerSelf			UMETA(DisplayName = "PlayerSelf"),
	PlayerVillager      UMETA(DisplayName = "PlayerVillager"),
	PlayerStation 		UMETA(DisplayName = "PlayerStation"),
	VillagerStation		UMETA(DisplayName = "VillagerStation")
};

UCLASS()
class VILLAGEBUILDER_API UDataLink : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere)
	AActor* Initiator;

	UPROPERTY()
	TMap<TEnumAsByte<EVisualiationTypes>, class UVisualizationInfo*> InitiatorInfo;

	UPROPERTY(VisibleAnywhere)
	AActor* Target;

	UPROPERTY()
	TMap<TEnumAsByte<EVisualiationTypes>, class UVisualizationInfo*> TargetInfo;

	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EDataLinkType> LinkType;

	bool bShouldVisualize = false;

	bool EstablishConnection();

public:

	UFUNCTION()
	void BreakConnection();

	FLinkBrokenSignature OnLinkBroken;

	static UDataLink* CreateDataLink(AActor* InInitiator, AActor* InTarget);

	TMap<TEnumAsByte<EVisualiationTypes>, class UVisualizationInfo*> GetInitiatorInfo() { return InitiatorInfo; }
	TMap<TEnumAsByte<EVisualiationTypes>, class UVisualizationInfo*> GetTargetInfo() { return TargetInfo; }
	bool GetShouldVisualize() { return bShouldVisualize; }
	IDataLinkable* GetInitiator();
	IDataLinkable* GetTarget();
};

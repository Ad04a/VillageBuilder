// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTransfers/VisualizationInfo.h"
#include "Headers/LoadInfo.h"
#include "EmploymentVisualInfo.generated.h"

USTRUCT(BlueprintType)
struct FStationStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText StationName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TEnumAsByte<ETrait>, float> ScalingMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int HiredID = -1;
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FEmpoloyeesUpdatedSignature, TArray<FVillagerVisualInfoStruct>, Villagers, FStationStruct, StationStruct);

UCLASS()
class VILLAGEBUILDER_API UEmploymentVisualInfo : public UVisualizationInfo
{
	GENERATED_BODY()
protected:
	class ABaseWorkStation* WorkStation;
	class AVillageManager* Village;

	UFUNCTION()
	void RecieveUpdatedVillagers(TArray<class AVillager*> Villagers);

public:
	static UVisualizationInfo* CreateVisualInfo(AActor* InActor);
	virtual void Clear() override;

	FEmpoloyeesUpdatedSignature OnVillagersUpdated;

	void InvokeInitial();

	UFUNCTION()
	void RegisterEmployment(int VillagerID);
};

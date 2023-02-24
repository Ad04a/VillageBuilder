// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataLink.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FLinkBrokenSignature, UDataLink*, BrokenLink);

UENUM(BlueprintType)
enum EDataLinkType {
	PlayerSelf			UMETA(DisplayName = "PlayerSelf"),
	PlayerVillager      UMETA(DisplayName = "PlayerVillager"),
	PlayerStation 		UMETA(DisplayName = "PlayerStation"),
	VillagerStation		UMETA(DisplayName = "VillagerStation")
};

UENUM(BlueprintType)
enum EVisualiationTypes {
	StatAndTrait UMETA(DisplayName = "StatAndTrait"),
	Inventory    UMETA(DisplayName = "Inventory"),
	Employment 	 UMETA(DisplayName = "Employment")
};

UCLASS()
class VILLAGEBUILDER_API UDataLink : public UObject
{
	GENERATED_BODY()

protected:

	static TMap<TEnumAsByte<EVisualiationTypes>, TSubclassOf<class UVisualizationInfo>> TypesMap;


	UPROPERTY(VisibleAnywhere)
	AActor* Initiator;

	UPROPERTY()
	TSubclassOf<AActor> InitiatorClass;

	UPROPERTY(VisibleAnywhere)
	AActor* Target;

	UPROPERTY()
	TSubclassOf<AActor> TargetClass;

	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EDataLinkType> LinkType;

	bool EstablishConnection();

	void BreakConnection();

	static void InitRelations();
public:

	FLinkBrokenSignature OnLinkBroken;

	static UDataLink* CreateDataLink(AActor* InInitiator, AActor* InTarget, EDataLinkType InLinkType = EDataLinkType::PlayerSelf);
};

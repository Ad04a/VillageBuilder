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

UCLASS()
class VILLAGEBUILDER_API UDataLink : public UObject
{
	GENERATED_BODY()

protected:
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

public:

	FLinkBrokenSignature OnLinkBroken;

	static UDataLink* CreateDataLink(AActor* InInitiator, AActor* InTarget, EDataLinkType InLinkType = EDataLinkType::PlayerSelf);
};

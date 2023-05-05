// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "Headers/Interfaces/Controlable.h"

#include "VillageBuilderSpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API AVillageBuilderSpectatorPawn : public ASpectatorPawn, public IControlable
{
	GENERATED_BODY()
	
public:
	virtual void UpdateMovement_Implementation(float MoveForwardValue, float MoveRightValue);

	virtual void PawnTurnAtRate_Implementation(float Rate);

	virtual void PawnLookUpAtRate_Implementation(float Rate);

	UPROPERTY(EditAnywhere)
	float TurnRateModifier = 0.5f;

	UPROPERTY(EditAnywhere)
	float FlySpeedModifier = 0.5f;

};

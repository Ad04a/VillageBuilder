// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Villager.h"
#include "VillageBuilderPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API AVillageBuilderPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	class AVillager* ControlledVillager;

protected:

	virtual void BeginPlay() override;

	void UpdateMovement(float DeltaTime);
	void UpdateTurnRotation();

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName LookUpBinding;
	static const FName TurnRightBinding;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	float GamepadTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	float MouseTurnRate = 20;

public:

	void Tick(float DeltaTime);
};

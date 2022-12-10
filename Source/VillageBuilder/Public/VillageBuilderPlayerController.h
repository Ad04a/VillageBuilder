// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Characters/Villager.h"
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

	virtual void OnPossess(APawn* InPawn) override;

	void UpdateMovement(float DeltaTime);
	void UpdateTurnRotation();

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName LookUpBinding;
	static const FName TurnRightBinding;
	static const FName InteractBinding;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	float GamepadTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	float MouseTurnRate = 20;

public:

	void Tick(float DeltaTime);
};

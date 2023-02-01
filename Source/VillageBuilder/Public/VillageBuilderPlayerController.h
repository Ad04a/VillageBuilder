// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Characters/VillageMayor.h"
#include "VillageBuilderPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API AVillageBuilderPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	class AVillageMayor* ControlledVillageMayorPawn;

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
	static const FName TraitsMenuBinding;
	static const FName ItemPrimaryBinding;
	static const FName ItemSecondaryBinding;
	static const FName DropItemBinding;
	
	
	void ItemPrimary();
	void ItemSecondary();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	float GamepadTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	float MouseTurnRate = 20;

public:

	void Tick(float DeltaTime);
};

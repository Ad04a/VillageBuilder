// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Villager.generated.h"

UCLASS()
class VILLAGEBUILDER_API AVillager : public ACharacter
{
	GENERATED_BODY()

private:
	bool IsMovementEnabled = true;
	bool IsRotationEnabled = true;

	FRotator MovementInputRotator;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	AVillager();
	virtual void Tick(float DeltaTime) override;

	void UpdateMovement(float MoveForwardValue, float MoveRightValue);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void SetIsMovementEnabled(bool State);
	void SetIsRotationEnabled(bool State);
	
	

};

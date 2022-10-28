// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager.h"

// Sets default values
AVillager::AVillager()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVillager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVillager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVillager::SetIsMovementEnabled(bool State)
{
	IsMovementEnabled = State;
}

void AVillager::SetIsRotationEnabled(bool State)
{
	IsRotationEnabled = State;
}

void AVillager::UpdateMovement(float MoveForwardValue, float MoveRightValue)
{
	if ( InputEnabled() == false || IsMovementEnabled == false)
	{
		return;
	}
	FVector CurrMoveDirection = FVector(MoveForwardValue, MoveRightValue, 0.f).GetClampedToMaxSize(1.0f);
	CurrMoveDirection = MovementInputRotator.RotateVector(CurrMoveDirection);

	AddMovementInput(CurrMoveDirection);
}

void AVillager::TurnAtRate(float Rate)
{
	if (InputEnabled() == false || IsRotationEnabled == false)
	{
		return;
	}
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::TurnAtRate IsValid(World) == false"));
		return;
	}
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate/* /(Rate*Tiredness))*/ * World->GetDeltaSeconds());
}

void AVillager::LookUpAtRate(float Rate)
{
	if (InputEnabled() == false || IsRotationEnabled == false)
	{
		return;
	}
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::LookUpAtRate IsValid(World) == false"));
		return;
	}
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate/* /(Rate*Tiredness))*/ * World->GetDeltaSeconds());
}



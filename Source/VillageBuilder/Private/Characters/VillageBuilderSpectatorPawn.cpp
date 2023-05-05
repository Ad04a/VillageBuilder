// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/VillageBuilderSpectatorPawn.h"

void AVillageBuilderSpectatorPawn::UpdateMovement_Implementation(float MoveForwardValue, float MoveRightValue)
{
	if (MoveForwardValue != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), MoveForwardValue * FlySpeedModifier);
	}
	if (MoveRightValue != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), MoveRightValue * FlySpeedModifier);
	}
}

void AVillageBuilderSpectatorPawn::PawnTurnAtRate_Implementation(float Rate)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::TurnAtRate IsValid(World) == false"));
		return;
	}
	TurnAtRate(Rate * TurnRateModifier * World->GetDeltaSeconds());
}

void AVillageBuilderSpectatorPawn::PawnLookUpAtRate_Implementation(float Rate)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::LookUpAtRate IsValid(World) == false"));
		return;
	}
	LookUpAtRate(Rate * TurnRateModifier * World->GetDeltaSeconds());

}
// Fill out your copyright notice in the Description page of Project Settings.

#include "Villager.h"
#include "VillageBuilderPlayerController.h"

const FName AVillageBuilderPlayerController::MoveForwardBinding("MoveForward");
const FName AVillageBuilderPlayerController::MoveRightBinding("MoveRight");
const FName AVillageBuilderPlayerController::LookUpBinding("LookUp");
const FName AVillageBuilderPlayerController::TurnRightBinding("TurnRight");

void AVillageBuilderPlayerController::BeginPlay()
{
	if (IsValid(InputComponent) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderPlayerController::BeginPlay IsValid(InputComponent) == false"));
		return;
	}

	ControlledVillager = Cast<AVillager>(GetCharacter());

	if (IsValid(ControlledVillager) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderPlayerController::BeginPlay IsValid(ControlledVillager) == false"));
		return;
	}


	//InputComponent->BindAction("PrimaryAction", IE_Pressed, ControlledCharacter, &ATestFPCharacter::OnPrimaryAction);

	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(MoveRightBinding);

	InputComponent->BindAxis(TurnRightBinding);
	InputComponent->BindAxis(LookUpBinding);
}

void AVillageBuilderPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMovement(DeltaTime);
	UpdateTurnRotation();
	UpdateRotation(DeltaTime);

	
}

void AVillageBuilderPlayerController::UpdateMovement(float DeltaTime)
{
	
	const float MoveForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float MoveRightValue = GetInputAxisValue(MoveRightBinding);

	if (MoveForwardValue!=0 || MoveRightValue!=0) {
		ControlledVillager->UpdateMovement(MoveForwardValue, MoveRightValue);
	}
}

void AVillageBuilderPlayerController::UpdateTurnRotation()
{
	float X = GetInputAxisValue(TurnRightBinding);
	float Y = GetInputAxisValue(LookUpBinding);

	X *= MouseTurnRate;
	Y *= MouseTurnRate;

	/*if (InputDeviceType == EInputDeviceType::Gamepad)
	{
		X *= GamepadTurnRate;
		Y *= GamepadTurnRate;
	}*/
	if (X != 0) {
		ControlledVillager->TurnAtRate(X);
	}

	if (Y != 0) {
		ControlledVillager->LookUpAtRate(Y);
	}
	
}




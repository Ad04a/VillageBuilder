// Fill out your copyright notice in the Description page of Project Settings.

#include "VillageBuilderPlayerController.h"
#include "UI/HUDS/GameplayHUDBase.h"

const FName AVillageBuilderPlayerController::MoveForwardBinding("MoveForward");
const FName AVillageBuilderPlayerController::MoveRightBinding("MoveRight");
const FName AVillageBuilderPlayerController::LookUpBinding("LookUp");
const FName AVillageBuilderPlayerController::TurnRightBinding("TurnRight");
const FName AVillageBuilderPlayerController::InteractBinding("Interact");
const FName AVillageBuilderPlayerController::TraitsMenuBinding("TraitsMenu");

void AVillageBuilderPlayerController::BeginPlay()
{
	
}

void AVillageBuilderPlayerController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	if (IsValid(InputComponent) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderPlayerController::BeginPlay IsValid(InputComponent) == false"));
		return;
	}

	ControlledVillager = Cast<AVillager>(GetCharacter());
	if (IsValid(ControlledVillager) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderPlayerController::OnPossess IsValid(ControlledVillager) == false"));
		return;
	}

	AGameplayHUDBase* HUD = Cast<AGameplayHUDBase>(GetHUD());
	if (IsValid(HUD) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderPlayerController::OnPossess IsValid(HUD) == false"));
		return;
	}

	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(MoveRightBinding);

	InputComponent->BindAxis(TurnRightBinding);
	InputComponent->BindAxis(LookUpBinding);

	InputComponent->BindAction(InteractBinding, IE_Pressed, ControlledVillager, &AVillager::Interact);
	InputComponent->BindAction(TraitsMenuBinding, IE_Pressed, ControlledVillager, &AVillager::ShowTraitMenu);

	HUD->BindPlayerToStatWidget(ControlledVillager);
	ControlledVillager->OnInteraction.AddDynamic(HUD, &AGameplayHUDBase::ShowInteraction);
	ControlledVillager->OnToggleTraitsMenu.AddDynamic(HUD, &AGameplayHUDBase::ShowTraitMenu);
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




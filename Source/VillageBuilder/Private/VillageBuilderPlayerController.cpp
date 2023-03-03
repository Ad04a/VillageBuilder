// Fill out your copyright notice in the Description page of Project Settings.

#include "VillageBuilderPlayerController.h"
#include "UI/HUDS/GameplayHUDBase.h"

const FName AVillageBuilderPlayerController::MoveForwardBinding("MoveForward");
const FName AVillageBuilderPlayerController::MoveRightBinding("MoveRight");
const FName AVillageBuilderPlayerController::LookUpBinding("LookUp");
const FName AVillageBuilderPlayerController::TurnRightBinding("TurnRight");
const FName AVillageBuilderPlayerController::TraitsMenuBinding("TraitsMenu");
const FName AVillageBuilderPlayerController::ItemPrimaryBinding("ItemPrimary");
const FName AVillageBuilderPlayerController::ItemSecondaryBinding("ItemSecondary");
const FName AVillageBuilderPlayerController::DropItemBinding("DropItem");
const FName AVillageBuilderPlayerController::InteractBinding("Interact");
const FName AVillageBuilderPlayerController::DataLinkBinding("DataLink");



void AVillageBuilderPlayerController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	if (IsValid(InputComponent) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderPlayerController::BeginPlay IsValid(InputComponent) == false"));
		return;
	}

	ControlledVillageMayorPawn = Cast<AVillageMayor>(GetCharacter());
	if (IsValid(ControlledVillageMayorPawn) == false) {
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

	InputComponent->BindAction(InteractBinding, IE_Pressed, ControlledVillageMayorPawn, &AVillageMayor::Interact);
	InputComponent->BindAction(DataLinkBinding, IE_Pressed, ControlledVillageMayorPawn, &AVillageMayor::InitiateLink);
	InputComponent->BindAction(TraitsMenuBinding, IE_Pressed, ControlledVillageMayorPawn, &AVillageMayor::ShowTraitMenu);
	InputComponent->BindAction(DropItemBinding, IE_Pressed, this, &AVillageBuilderPlayerController::CaptureDrop);

	HUD->ShowMainWidget(ControlledVillageMayorPawn);

	InPawn->bUseControllerRotationYaw = true;

	InputComponent->BindAction(ItemPrimaryBinding, IE_Pressed, this, &AVillageBuilderPlayerController::ItemPrimary);
	InputComponent->BindAction(ItemSecondaryBinding, IE_Pressed, this, &AVillageBuilderPlayerController::ItemSecondary);
}

void AVillageBuilderPlayerController::CaptureDrop()
{
	ControlledVillageMayorPawn->DropItem();
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
		ControlledVillageMayorPawn->UpdateMovement(MoveForwardValue, MoveRightValue);
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
		ControlledVillageMayorPawn->TurnAtRate(X);
	}

	if (Y != 0) {
		ControlledVillageMayorPawn->LookUpAtRate(Y);
	}
	
}

void AVillageBuilderPlayerController::ItemPrimary()
{
	ControlledVillageMayorPawn->UseItem(EItemActionType::Primary);
}
void AVillageBuilderPlayerController::ItemSecondary()
{
	ControlledVillageMayorPawn->UseItem(EItemActionType::Secondary);
}





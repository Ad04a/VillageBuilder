// Fill out your copyright notice in the Description page of Project Settings.

#include "VillageBuilderPlayerController.h"
#include "UI/HUDS/GameplayHUDBase.h"

const FName AVillageBuilderPlayerController::MoveForwardBinding("MoveForward");
const FName AVillageBuilderPlayerController::MoveRightBinding("MoveRight");
const FName AVillageBuilderPlayerController::LookUpBinding("LookUp");
const FName AVillageBuilderPlayerController::TurnRightBinding("TurnRight");
const FName AVillageBuilderPlayerController::InteractBinding("Interact");
const FName AVillageBuilderPlayerController::TraitsMenuBinding("TraitsMenu");
const FName AVillageBuilderPlayerController::RightHandPrimaryBinding("RightHandPrimary");
const FName AVillageBuilderPlayerController::RightHandSecondaryBinding("RightHandSecondary");
const FName AVillageBuilderPlayerController::LeftHandPrimaryBinding("LeftHandPrimary");
const FName AVillageBuilderPlayerController::LeftHandSecondaryBinding("LeftHandSecondary");

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

	InPawn->bUseControllerRotationYaw = true;

	InputComponent->BindAction(RightHandPrimaryBinding, IE_Pressed, this, &AVillageBuilderPlayerController::RightHandPrimary);
	InputComponent->BindAction(RightHandSecondaryBinding, IE_Pressed, this, &AVillageBuilderPlayerController::RightHandSecondary);
	InputComponent->BindAction(LeftHandPrimaryBinding, IE_Pressed, this, &AVillageBuilderPlayerController::LeftHandPrimary);
	InputComponent->BindAction(LeftHandSecondaryBinding, IE_Pressed, this, &AVillageBuilderPlayerController::LeftHandSecondary);
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

void AVillageBuilderPlayerController::RightHandPrimary()
{
	ControlledVillager->ItemAction(EVillagerItemSlot::RightHand, EHandActionType::Primary);
}
void AVillageBuilderPlayerController::RightHandSecondary()
{
	ControlledVillager->ItemAction(EVillagerItemSlot::RightHand, EHandActionType::Secondary);
}
void AVillageBuilderPlayerController::LeftHandPrimary()
{
	ControlledVillager->ItemAction(EVillagerItemSlot::LeftHand, EHandActionType::Primary);
}
void AVillageBuilderPlayerController::LeftHandSecondary()
{
	ControlledVillager->ItemAction(EVillagerItemSlot::LeftHand, EHandActionType::Secondary);
}




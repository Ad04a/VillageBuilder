// Fill out your copyright notice in the Description page of Project Settings.

#include "VillageBuilderPlayerController.h"
#include "UI/HUDS/GameplayHUDBase.h"
#include "DataTransfers/DataLink.h"
#include "Headers/Interfaces/Controlable.h"

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

void AVillageBuilderPlayerController::BeginPlay()
{
	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(MoveRightBinding);

	InputComponent->BindAxis(TurnRightBinding);
	InputComponent->BindAxis(LookUpBinding);


	InputComponent->BindAction(InteractBinding, IE_Pressed, this, &AVillageBuilderPlayerController::Interact);
	InputComponent->BindAction(DataLinkBinding, IE_Pressed, this, &AVillageBuilderPlayerController::InitiateLink);
	InputComponent->BindAction(TraitsMenuBinding, IE_Pressed, this, &AVillageBuilderPlayerController::ShowTraitMenu);
	InputComponent->BindAction(DropItemBinding, IE_Pressed, this, &AVillageBuilderPlayerController::CaptureDrop);

	InputComponent->BindAction(ItemPrimaryBinding, IE_Pressed, this, &AVillageBuilderPlayerController::ItemPrimary);
	InputComponent->BindAction(ItemSecondaryBinding, IE_Pressed, this, &AVillageBuilderPlayerController::ItemSecondary);
}

void AVillageBuilderPlayerController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	InPawn->bUseControllerRotationYaw = true;

	if (IsValid(InputComponent) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderPlayerController::BeginPlay IsValid(InputComponent) == false"));
		return;
	}

	ControlledVillageMayorPawn = Cast<AVillageMayor>(GetCharacter());

	AGameplayHUDBase* HUD = Cast<AGameplayHUDBase>(GetHUD());
	if (IsValid(HUD) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillageBuilderPlayerController::OnPossess IsValid(HUD) == false"));
		return;
	}

	if (IsValid(ControlledVillageMayorPawn)==false)
	{
		UE_LOG(LogTemp, Display, TEXT("AVillageBuilderPlayerController::OnPossess IsValid(ControlledVillageMayorPawn)==false"));
		return;
	}
	
	HUD->ShowMainWidget(ControlledVillageMayorPawn);
	ControlledVillageMayorPawn->OnDeath.AddDynamic(this, &AVillageBuilderPlayerController::OnPlayerDeath);

	OnVillagerDeath.BindDynamic(HUD, &AGameplayHUDBase::Clear);

	
}

void AVillageBuilderPlayerController::CaptureDrop()
{
	if (IsPlayerValid() == false)
	{
		return;
	}
	ControlledVillageMayorPawn->DropItem();
}

void AVillageBuilderPlayerController::Interact()
{
	if (IsPlayerValid() == false)
	{
		OpenSpectatorMenu();
		return;
	}
	ControlledVillageMayorPawn->Interact();
}

void AVillageBuilderPlayerController::InitiateLink()
{
	if (IsPlayerValid() == false)
	{
		OpenSpectatorMenu();
		return;
	}
	ControlledVillageMayorPawn->InitiateLink();
}

void AVillageBuilderPlayerController::ShowTraitMenu()
{
	if (IsPlayerValid() == false)
	{
		OpenSpectatorMenu();
		return;
	}
	ControlledVillageMayorPawn->ShowTraitMenu();
}

void AVillageBuilderPlayerController::Init(FPlayerControllerInfoStruct InLoadInfo)
{
	CurrentSurvivedTime = InLoadInfo.CurrentSurvivedTime;
}

FPlayerControllerInfoStruct AVillageBuilderPlayerController::GetSaveInfo()
{
	FPlayerControllerInfoStruct SaveInfo;
	SaveInfo.CurrentSurvivedTime = CurrentSurvivedTime;
	return SaveInfo;
}

void AVillageBuilderPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentSurvivedTime += DeltaTime;

	UpdateMovement(DeltaTime);
	UpdateTurnRotation();
	UpdateRotation(DeltaTime);

}

void AVillageBuilderPlayerController::OpenSpectatorMenu()
{
	UDataLink::CreateDataLink(this, nullptr);
}

void AVillageBuilderPlayerController::OnPlayerDeath(AVillager* Villager)
{
	OnVillagerDeath.ExecuteIfBound();

	ControlledVillageMayorPawn->Destroy();
	ControlledVillageMayorPawn = nullptr;

	OpenSpectatorMenu();
}

void AVillageBuilderPlayerController::UpdateMovement(float DeltaTime)
{
	IControlable* ControlledPawn = Cast<IControlable>(GetPawnOrSpectator());

	if (ControlledPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT(" AVillageBuilderPlayerController::UpdateMovement ControlledPawn == nullptr"));
		return;
	}

	const float MoveForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float MoveRightValue = GetInputAxisValue(MoveRightBinding);

	if (MoveForwardValue!=0 || MoveRightValue!=0) {
		ControlledPawn->Execute_UpdateMovement(GetPawnOrSpectator(), MoveForwardValue, MoveRightValue);
	}
}

void AVillageBuilderPlayerController::UpdateTurnRotation()
{
	IControlable* ControlledPawn = Cast<IControlable>(GetPawnOrSpectator());

	if (ControlledPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT(" AVillageBuilderPlayerController::UpdateTurnRotation ControlledPawn == nullptr"));
		return;
	}

	float X = GetInputAxisValue(TurnRightBinding);
	float Y = GetInputAxisValue(LookUpBinding);

	X *= MouseTurnRate;
	Y *= MouseTurnRate;

	if (X != 0) {
		ControlledPawn->Execute_PawnTurnAtRate(GetPawnOrSpectator(), X);
	}

	if (Y != 0) {
		ControlledPawn->Execute_PawnLookUpAtRate(GetPawnOrSpectator(), Y);
	}
	
}

void AVillageBuilderPlayerController::ItemPrimary()
{
	if (IsPlayerValid() == false)
	{
		OpenSpectatorMenu();
		return;
	}
	ControlledVillageMayorPawn->UseItem(EItemActionType::Primary);
}
void AVillageBuilderPlayerController::ItemSecondary()
{
	if (IsPlayerValid() == false)
	{
		OpenSpectatorMenu();
		return;
	}
	ControlledVillageMayorPawn->UseItem(EItemActionType::Secondary);
}

bool AVillageBuilderPlayerController::IsPlayerValid()
{
	return IsValid(GetCharacter());
}



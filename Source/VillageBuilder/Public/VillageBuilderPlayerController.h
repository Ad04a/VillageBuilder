// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Characters/VillageMayor.h"
#include "VillageBuilderPlayerController.generated.h"

DECLARE_DYNAMIC_DELEGATE(FVillagerDeathSignature);

USTRUCT(BlueprintType)
struct FPlayerControllerInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CurrentSurvivedTime = 0;

};

UCLASS()
class VILLAGEBUILDER_API AVillageBuilderPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	class AVillageMayor* ControlledVillageMayorPawn;

protected:

	virtual void OnPossess(APawn* InPawn) override;

	void UpdateMovement(float DeltaTime);
	void UpdateTurnRotation();

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName LookUpBinding;
	static const FName TurnRightBinding;
	static const FName TraitsMenuBinding;
	static const FName ItemPrimaryBinding;
	static const FName ItemSecondaryBinding;
	static const FName DropItemBinding;
	static const FName InteractBinding;
	static const FName DataLinkBinding;
	
	void ItemPrimary();
	void ItemSecondary();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	float GamepadTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	float MouseTurnRate = 20;

	UFUNCTION()
	void CaptureDrop();
	UFUNCTION()
	void Interact();
	UFUNCTION()
	void InitiateLink();
	UFUNCTION()
	void ShowTraitMenu();

	UFUNCTION()
	void OnPlayerDeath(AVillager* Villager);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Playtime)
	float CurrentSurvivedTime = 0;

	UFUNCTION()
	void OpenSpectatorMenu();

	FVillagerDeathSignature OnVillagerDeath;

public:

	void Init(FPlayerControllerInfoStruct InLoadInfo);
	FPlayerControllerInfoStruct GetSaveInfo();

	void Tick(float DeltaTime);

	bool IsPlayerValid();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Villager.h"
#include "Camera/CameraComponent.h"
#include "WorkSystem/BaseWorkStation.h"
#include "VillageMayor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraitMenuSignature, AVillager*, Caller);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractingSignature, FText, ActionText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEmployeeMenuSignature, ABaseWorkStation*, WorkStation);

UCLASS()
class VILLAGEBUILDER_API AVillageMayor : public AVillager
{
	GENERATED_BODY()

public:
	AVillageMayor();

private:

	void CheckForInteractables();

	UObject* FocusedObject;

	bool CanInteract = true;

protected:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory)
	float Reach = 1;

	UFUNCTION()
	void ToggleStableInteraction();

public:

	FInteractingSignature OnInteraction;
	FTraitMenuSignature OnToggleTraitsMenu;
	FEmployeeMenuSignature OnToggleEmployeeMenu;

	bool bIsInteracting = false;

	UFUNCTION()
	void ShowTraitMenu();

	UFUNCTION()
	void ToggleTraitsMenu(AVillager* Caller);

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void ToggleEmployeeMenu(ABaseWorkStation* WorkStation);
	
};

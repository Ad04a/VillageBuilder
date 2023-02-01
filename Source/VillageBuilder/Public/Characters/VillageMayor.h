// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Villager.h"
#include "Camera/CameraComponent.h"
#include "VillageMayor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraitMenuSignature, AVillager*, Caller);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractingSignature, FText, ActionText);


UCLASS()
class VILLAGEBUILDER_API AVillageMayor : public AVillager
{
	GENERATED_BODY()

public:
	AVillageMayor();

private:

	void CheckForInteractables();

	AActor* FocusedActor;

	bool CanInteract = true;

protected:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory)
	float Reach = 1;

public:

	FInteractingSignature OnInteraction;
	FTraitMenuSignature OnToggleTraitsMenu;

	bool IsInteracting = false;

	UFUNCTION()
	void ShowTraitMenu();

	UFUNCTION()
	void ToggleTraitsMenu(AVillager* Caller);

	UFUNCTION()
	void Interact();
	
};

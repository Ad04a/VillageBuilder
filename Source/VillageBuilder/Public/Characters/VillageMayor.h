// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Villager.h"
#include "Camera/CameraComponent.h"
#include "WorkSystem/BaseWorkStation.h"
#include "VillageMayor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractingSignature, FText, ActionText);

UCLASS()
class VILLAGEBUILDER_API AVillageMayor : public AVillager
{
	GENERATED_BODY()

public:
	AVillageMayor();

private:

	void EmitChecker();

	void CheckForInteractables(AActor* HitActor);

	AActor* FocusedInteractableObject;

	void CheckForDataLinks(AActor* HitActor);

	AActor* FocusedDataLinkableObject;

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
	FInteractingSignature OnDataLink;

	UFUNCTION()
	void ShowTraitMenu();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void InitiateLink();

	UCameraComponent* GetCameraComponent()const { return CameraComponent; };
	
};

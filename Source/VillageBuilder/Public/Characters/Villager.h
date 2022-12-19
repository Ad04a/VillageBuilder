// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "InteractableObjects/Interactable.h"
#include "Headers/StatAndTraitStructure.h"
#include "Villager.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FStatUpdatedSignature, EStat, StatName, float, Current, float, Max);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraitMenuSignature, AVillager*, Caller);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractingSignature, FText, ActionText);


UCLASS()
class VILLAGEBUILDER_API AVillager : public ACharacter, public IInteractable
{
	GENERATED_BODY()

private:
	float StatDepletion = 0;

	void Die();

	void CheckForInteractables();

	AActor* FocusedActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY()
	FLoadInfoStruct LoadInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Traits)
	TMap<TEnumAsByte<ETrait>, FTraitInfoStruct> TraitsMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	TMap<TEnumAsByte<EStat>, FStatInfoStruct> StatsMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	TMap<TEnumAsByte<EStat>, TEnumAsByte<ETrait>> StatTraitRelation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Traits)
	int TraitsCap = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float StatDepletionInterval = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float SaturationForPassiveHealing = 0.5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Inventory)
	float Reach = 1;

	

	FRotator MovementInputRotator;

	//FJobInfoStruct JobInfo

public:	

	FStatUpdatedSignature OnStatUpdated;
	FInteractingSignature OnInteraction;
	FTraitMenuSignature OnToggleTraitsMenu;

	AVillager();
	virtual void Tick(float DeltaTime) override;

	void UpdateMovement(float MoveForwardValue, float MoveRightValue);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	bool IsMovementEnabled = true;
	bool IsRotationEnabled = true;
	bool IsInteracting = false;
	bool CanInteract = true;

	void Init(FLoadInfoStruct InLoadInfo = FLoadInfoStruct()/*InColonyState*/);
	FLoadInfoStruct SaveInfo();
	void RecieveXP(ETrait, int XPAmount);
	void AssignJob(/*(FJobInfoStruct InJobInfo)/(WorkStation)*/);

	void AcknowledgeWidgetBinding();

	void AddStatValue(EStat StatName, float InValue);

	int GetTrait(ETrait TraitName);

	UFUNCTION()
	void ShowTraitMenu();

	UFUNCTION()
	void ToggleTraitsMenu(AVillager* Caller);

	UFUNCTION()
	void Interact();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractRequest(class AVillager* InteractingVillager);
	virtual void InteractRequest_Implementation(class AVillager* InteractingVillager);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FText DisplayInteractText();
	virtual FText DisplayInteractText_Implementation();
};

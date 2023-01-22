// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "InteractableObjects/Items/Item.h"
#include "Headers/Interactable.h"
#include "Headers/LoadInfo.h"
#include "Headers/ItemActionEnums.h"
#include "Villager.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FStatUpdatedSignature, EStat, StatName, float, Current, float, Max);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraitMenuSignature, AVillager*, Caller);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractingSignature, FText, ActionText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemActionSignature, EItemActionType, ItemActionType);


UCLASS()
class VILLAGEBUILDER_API AVillager : public ACharacter, public IInteractable
{
	GENERATED_BODY()

private:
	float StatDepletion = 0;

	void Die();

	void CheckForInteractables();

	AActor* FocusedActor;

	AItem* ItemSlot;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float TakeDamage(float DamageAmount,
		FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser)override;

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
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Item Action"))
	FOnItemActionSignature OnItemAction;

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
	FLoadInfoStruct GetSaveInfo();
	void RecieveXP(ETrait, int XPAmount);
	void AssignJob(/*(FJobInfoStruct InJobInfo)/(WorkStation)*/);

	void AcknowledgeWidgetBinding();

	void AddStatValue(EStat StatName, float InValue);

	UFUNCTION()
	void ShowTraitMenu();

	UFUNCTION()
	void ToggleTraitsMenu(AVillager* Caller);

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void Equip(class AActor* ItemToEquip);

	UFUNCTION()
	void DropItem();

	UFUNCTION()
	void ItemAction(EItemActionType ActionType);

	UFUNCTION()
	void UseItem(EItemActionType ActionType);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractRequest(class AActor* InteractingActor);
	virtual void InteractRequest_Implementation(class AActor* InteractingActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FText DisplayInteractText();
	virtual FText DisplayInteractText_Implementation();

	int GetTrait(ETrait TraitName);

	UFUNCTION(BlueprintPure)
	EItemType GetEquipItemType();

};

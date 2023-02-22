// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Items/Item.h"
#include "Headers/Interactable.h"
#include "Headers/LoadInfo.h"
#include "Headers/ItemActionEnums.h"
#include "Villager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FStatUpdatedSignature, EStat, StatName, float, Current, float, Max);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVillagerPassingSignature, AVillager*, Villager);

UCLASS()
class VILLAGEBUILDER_API AVillager : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	AVillager();

private:

	float StatDepletion = 0;

	void Die();

	AItem* ItemSlot;

	AVillager* InteractingWith = nullptr;


protected:
	virtual void Tick(float DeltaTime) override;

	FString Name = "Name";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDataTable* StatTraitDataTable = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName RollToRead = "Default";

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

	FRotator MovementInputRotator;

	bool bCanUseItems = true;

	void CalculateStats();

	UFUNCTION()
	void RecieveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:	

	FStatUpdatedSignature OnStatUpdated;
	FVillagerPassingSignature OnDeath;

	void UpdateMovement(float MoveForwardValue, float MoveRightValue);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void PlayItemAnimMontage(UAnimMontage* AnimMontage, FName StartSectionName);

	bool bIsMovementEnabled = true;
	bool bIsRotationEnabled = true;

	void Init(FVillagerLoadInfoStruct InLoadInfo = FVillagerLoadInfoStruct(), FString InName="");
	FVillagerLoadInfoStruct GetSaveInfo();
	void RecieveXP(ETrait, int XPAmount);

	void AcknowledgeWidgetBinding();

	void AddStatValue(EStat StatName, float InValue);

	UFUNCTION()
	void Equip(class AActor* ItemToEquip);

	UFUNCTION()
	void DropItem();

	UFUNCTION()
	void UseItem(EItemActionType ActionType);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractRequest(class AVillager* InteractingVillager);
	virtual void InteractRequest_Implementation(class AVillager* InteractingVillager);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FText DisplayInteractText();
	virtual FText DisplayInteractText_Implementation();

	FString GetName() { return Name; }
	int GetTrait(ETrait TraitName);
	AItem* GetItem()const { return ItemSlot; }
	class ABaseWorkStation* GetWorkStation();
	FText GetProfession();

	UFUNCTION(BlueprintPure)
	EItemType GetEquipItemType();

	bool CanEquip() { return !IsValid(ItemSlot); }

};

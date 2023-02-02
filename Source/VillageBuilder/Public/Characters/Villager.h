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

USTRUCT(BlueprintType)
struct FStatTraitData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Traits)
	TMap<TEnumAsByte<ETrait>, FTraitInfoStruct> TraitsMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	TMap<TEnumAsByte<EStat>, FStatInfoStruct> StatsMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	TMap<TEnumAsByte<EStat>, TEnumAsByte<ETrait>> StatTraitRelation;
};

UCLASS()
class VILLAGEBUILDER_API AVillager : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	AVillager();

private:

	AActor* WorkStation;

	float StatDepletion = 0;

	void Die();

	AItem* ItemSlot;


protected:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	FLoadInfoStruct LoadInfo;

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

	UFUNCTION()
	void RecieveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	//FJobInfoStruct JobInfo

public:	

	FStatUpdatedSignature OnStatUpdated;

	void UpdateMovement(float MoveForwardValue, float MoveRightValue);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void PlayItemAnimMontage(UAnimMontage* AnimMontage, FName StartSectionName);

	bool IsMovementEnabled = true;
	bool IsRotationEnabled = true;

	void Init(FLoadInfoStruct InLoadInfo = FLoadInfoStruct()/*InColonyState*/);
	FLoadInfoStruct GetSaveInfo();
	void RecieveXP(ETrait, int XPAmount);
	void AssignJob(/*(FJobInfoStruct InJobInfo)/(WorkStation)*/);

	void AcknowledgeWidgetBinding();

	void AddStatValue(EStat StatName, float InValue);

	UFUNCTION()
	void Equip(class AActor* ItemToEquip);

	UFUNCTION()
	void DropItem();

	UFUNCTION()
	void UseItem(EItemActionType ActionType);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractRequest(class AVillageMayor* InteractingPlayer);
	virtual void InteractRequest_Implementation(class AVillageMayor* InteractingPlayer);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FText DisplayInteractText();
	virtual FText DisplayInteractText_Implementation();

	int GetTrait(ETrait TraitName);
	AItem* GetItem() { return ItemSlot; }

	UFUNCTION(BlueprintPure)
	EItemType GetEquipItemType();

	bool GetIsUnemployed();
	FVector GetWorkStationCoordinates();

};

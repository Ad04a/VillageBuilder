// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Villager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStatUpdatedSignature, float, Percent);

UENUM(BlueprintType)
enum ETrait {
	Vitality      UMETA(DisplayName = "Vitality"),
	Survivability UMETA(DisplayName = "Survivability"),
	Agility       UMETA(DisplayName = "Agility"),
	Strength      UMETA(DisplayName = "Strength"),
	Dexterity     UMETA(DisplayName = "Dexterity")
};

UENUM(BlueprintType)
enum EStat {
	//Default UMETA(Displayname = "Default")
	Health  UMETA(DisplayName = "Health"),
	Energy  UMETA(DisplayName = "Energy"),
	Hunger  UMETA(DisplayName = "Hunger"),
	Thirst  UMETA(DisplayName = "Thirst"),
	Speed   UMETA(DisplayName = "Speed")
};

USTRUCT(BlueprintType)
struct FStatInfoStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	int Default = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	int PerLevel = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	int Max = 50;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	int Current = Max;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	int ChangeValue = 1;

};

USTRUCT(BlueprintType)
struct FTraitInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	int Level = 1;

	UPROPERTY(EditDefaultsOnly)
	FString Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Level)
	bool CanLevelUp = true;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Level)
	int CurrentXp = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Level)
	int NeededXpPerLevel = 10;
};

USTRUCT(BlueprintType)
struct FLoadInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<TEnumAsByte<EStat>, FStatInfoStruct> StatsMap;

	UPROPERTY()
	TMap<TEnumAsByte<ETrait>, FTraitInfoStruct> TraitsMap;

	UPROPERTY()
	FTransform Position;
	/*, InWorkPlace*/
};

UCLASS()
class VILLAGEBUILDER_API AVillager : public ACharacter
{
	GENERATED_BODY()

private:
	float StatDepletion = 0;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Traits)
	float StatDepletionInterval = 1;

	bool IsMovementEnabled = true;
	bool IsRotationEnabled = true;

	FRotator MovementInputRotator;

	//FJobInfoStruct JobInfo

public:	

	FStatUpdatedSignature OnHungerUpdated;
	FStatUpdatedSignature OnThirstUpdated;
	FStatUpdatedSignature OnEnergyUpdated;
	FStatUpdatedSignature OnHealthUpdated;

	AVillager();
	virtual void Tick(float DeltaTime) override;

	void UpdateMovement(float MoveForwardValue, float MoveRightValue);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void SetIsMovementEnabled(bool State);
	void SetIsRotationEnabled(bool State);

	void Init(/*InGlobalTimeManager, InControllerType , InColonyState*/);
	FLoadInfoStruct SaveInfo();
	void Load(FLoadInfoStruct InLoadInfo);
	void RecieveXP(ETrait, int XPAmount);
	void AssignJob(/*(FJobInfoStruct InJobInfo)/(WorkStation)*/);

	void AcknowledgeStatWidgetBinding();

	void SetStat(EStat StatName, int InValue, FStatUpdatedSignature DelegateToUpdate);
	

};

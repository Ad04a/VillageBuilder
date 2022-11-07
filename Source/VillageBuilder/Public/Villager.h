// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Villager.generated.h"

USTRUCT(BlueprintType)
struct FStatStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	int TicksToDecay = 72;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	int Starting = TicksToDecay/10;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Stats)
	int Max = Starting;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Stats)
	int Current = Max;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	int DepletionRate = 1;  //(DeplantionRate = Max/(Endurace * 5%Max)) --------- 100/((x/4)*(x/4)+6)
};

USTRUCT(BlueprintType)
struct FTraitInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	int Value;

	UPROPERTY()
		FString Description;
};

USTRUCT(BlueprintType)
struct FLoadInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FString, FStatStruct> StatsMap;

	UPROPERTY()
	TMap<FString, FTraitInfoStruct> TraitsMap;

	UPROPERTY()
	int CurrentLevel;

	UPROPERTY()
	int CurrentXP; 

	UPROPERTY()
	FVector Position;
	/*, InWorkPlace*/
};



UCLASS()
class VILLAGEBUILDER_API AVillager : public ACharacter
{
	GENERATED_BODY()

private:
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY()
	FLoadInfoStruct LoadInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Traits)
	TMap<FString, FTraitInfoStruct> TraitsMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	TMap<FString, FStatStruct> StatsMap;

	TMap<FString, TSet<FString>> AdditionTraitStatRelation;
	TMap<FString, TSet<FString>> DeplentionTraitStatRelation;

	/*UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Traits)
	int Vitality = 1; -- max health, max hunger
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Traits)
	int Endurance = 1; -- max stamina, max thirst
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Traits)
	int Strenght = 1; -- attk dmg
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Traits)
	int Dexterity = 1; -- attk + craftin speed
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Traits)
	int Atletics = 1; -- drop off stamina
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Traits)
	int Survavabilty = 1; -- hunger i thirst dropoff*/ 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Traits)
	int TraitsCap = 20;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Level)
	int LevelCap = 10;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Level)
	int CurrentLevel = 1;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Level)
	int CurrentXp = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Level)
	int NeededXpPerLevel = 100;

	bool IsMovementEnabled = true;
	bool IsRotationEnabled = true;

	FRotator MovementInputRotator;

	//FJobInfoStruct JobInfo;

	void LevelUp();
	void CalculateStats();

public:	
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
	void RecieveXP(int XPAmount);
	void AssignJob(/*(FJobInfoStruct InJobInfo)/(WorkStation)*/);
	

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Headers/AIStates.h"
#include "SignificanceManager.h"
#include "Animal.generated.h"

UCLASS()
class VILLAGEBUILDER_API AAnimal : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAnimal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bIsAcitve = true;

	UPROPERTY(EditDefaultsOnly)
	class UItemCarrierComponent* ItemCarrierComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float LifeTime = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentLifeTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health = 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DespawnDistance = 6000;

	UFUNCTION()
	void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void Die();

	float CalculateSignificance(USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint);
	void PostSignificanceCalculation(USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Signifcance, bool bFinal);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FAIStateSignature OnStateChanged;

	void Init(float InLifeTime, float InDespawnDistance);
	void Activate();
	void Disable();
};

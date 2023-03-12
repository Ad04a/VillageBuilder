// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "SignificanceManager.h"
#include "SpawningGridComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnReqestSignature, FVector, OriginLocation);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VILLAGEBUILDER_API USpawningGridComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawningGridComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Grid)
	float DisableRadius = 0;

	UPROPERTY(EditAnywhere, Category = Grid)
	float EnableRadius = 0;

	UPROPERTY(EditAnywhere, Category = Spawning)
	TArray<TSubclassOf<class AAnimal>> AnimalTypes;

	float CalculateSignificance(USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint);
	void PostSignificanceCalculation(USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Signifcance, bool bFinal);

	bool bIsActive = false;

	void SetIsActive(bool State);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FSpawnReqestSignature OnSpawnInitiated;

	void Init(FVector InLocation, float InEnableRadius, float InDisableRadius);

	UFUNCTION()
	void CaptureSpawn();
};

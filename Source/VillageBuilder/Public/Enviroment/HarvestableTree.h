// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enviroment/HarvestableActor.h"
#include "HarvestableTree.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API AHarvestableTree : public AHarvestableActor
{
	GENERATED_BODY()

public:
	AHarvestableTree();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBoxComponent* DestroyCollision = nullptr;

	UFUNCTION()
	void OnTreeFallen(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;
	
};

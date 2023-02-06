// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h" 
#include "BuildProjection.generated.h"

UCLASS()
class VILLAGEBUILDER_API ABuildProjection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildProjection();

private:
	bool bIsValid = true;
protected:
	void SetMaterial(UMaterialInterface* Material);

	UFUNCTION()
	void SetValid(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void SetInvalid(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBoxComponent* CollisionBox = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* ValidMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* InvalidMaterial;

public:	
	bool GetIsValid() { return bIsValid; }

};

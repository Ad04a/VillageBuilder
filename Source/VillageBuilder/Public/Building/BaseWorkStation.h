// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/Villager.h"
#include "BaseWorkStation.generated.h"

UCLASS()
class VILLAGEBUILDER_API ABaseWorkStation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWorkStation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AVillager* HiredVillager = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent = nullptr;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

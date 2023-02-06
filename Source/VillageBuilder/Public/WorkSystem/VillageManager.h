// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Headers/StatAndTraitStructure.h"
#include "Characters/Villager.h"
#include "WorkSystem/BaseWorkStation.h"
#include "VillageManager.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FVilligersUpdatedSignature, TArray<AVillager*>, Villagers);


UCLASS()
class VILLAGEBUILDER_API AVillageManager : public AActor 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVillageManager();

private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	TArray<AVillager*> PassingVillagers;
	UPROPERTY(VisibleAnywhere)
	TArray<AVillager*> Villagers;
	UPROPERTY(EditAnywhere)
	TMap<ABaseWorkStation*, AVillager*> WorkStations; //(WorkStation, HiredVillager)
	/*UPROPERTY()
	TMap<AVillager*, int VillagerId> Beds;*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AVillager> VillagerClass;

	UFUNCTION()
	AVillager* SpawnVillager(FVector Position = FVector(0, 0, 0), FLoadInfoStruct LoadInfo = FLoadInfoStruct());

	UFUNCTION()
	void OnVillagerDeath(AVillager* Villager);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVilligersUpdatedSignature OnVillagersUpdated;

	void AddVillagerToColony(AVillager* Villager);

	TArray<AVillager*> GetAllVillagers() { return Villagers; }
	AVillager* GetWorkerAt(ABaseWorkStation* WorkStation);
	ABaseWorkStation* GetWorkPlaceFor(AVillager* Worker);
	UFUNCTION()
	void ManageEmployment(ABaseWorkStation* WorkStation, AVillager* Worker);
};

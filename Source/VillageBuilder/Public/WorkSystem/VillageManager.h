// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Headers/StatAndTraitStructure.h"
#include "Characters/Villager.h"
#include "WorkSystem/BaseWorkStation.h"
#include "VillageManager.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FVilligersUpdatedSignature, TArray<AVillager*>, Villagers);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStateUpdatedSignature);

USTRUCT(BlueprintType)
struct FVillageManagerLoadInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FVillagerLoadInfoStruct> PassingVillagers = TArray<FVillagerLoadInfoStruct>();

	UPROPERTY()
	TArray<FVillagerLoadInfoStruct> Villagers = TArray<FVillagerLoadInfoStruct>();

	UPROPERTY()
	TArray<FWorkStationInfoStruct> WorkStations = TArray<FWorkStationInfoStruct>();
	
	UPROPERTY()
	TMap<int, int> WorkPlaces;

	UPROPERTY()
	FTransform Transform;

	inline bool operator==(const FVillageManagerLoadInfoStruct& other) const
	{
		return other.Transform.GetLocation() == Transform.GetLocation();
	}
	inline bool operator != (const FVillageManagerLoadInfoStruct& other) const
	{
		return !(other.Transform.GetLocation() == Transform.GetLocation());
	}
};

UCLASS()
class VILLAGEBUILDER_API AVillageManager : public AActor 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVillageManager();

private:
	void ApplyJobBehavior(FName StationName, AVillager* Worker);
	FTimerHandle SpawnHandle;
	bool bCanGenerateSaves = true;
	UPROPERTY(VisibleAnywhere, Category = Identification)
	unsigned int CurrentID = 0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	TArray<AVillager*> PassingVillagers;

	UPROPERTY(VisibleAnywhere)
	TArray<AVillager*> Villagers;

	UPROPERTY(VisibleAnywhere)
	TMap<ABaseWorkStation*, int> WorkStations; //(WorkStation, HiredVillager)

	UPROPERTY(VisibleAnywhere)
	TArray<ABaseWorkStation*> UnderConstruction;

	UPROPERTY(VisibleAnywhere)
	TArray<ABaseWorkStation*> PlacedBuildings;
	/*UPROPERTY()
	TMap<AVillager*, int VillagerId> Beds;  **/
	UPROPERTY(EditDefaultsOnly)
	UDataTable* BehaviorDataTable;

	UPROPERTY(EditDefaultsOnly)
	TMap<FName, UBehaviorTree*> WorkerBehaviors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AVillager> VillagerClass;

	UFUNCTION()
	AVillager* SpawnVillager(FVector Position = FVector(0, 0, 0), FVillagerLoadInfoStruct LoadInfo = FVillagerLoadInfoStruct());

	UFUNCTION()
	void OnVillagerDeath(AVillager* Villager);

	UFUNCTION()
	void AknowedgeFinishedBuilding(ABaseWorkStation* WorkStation);

	UFUNCTION()
	void AknowedgeStartedConstruction(bool State, ABaseWorkStation* WorkStation);

	UPROPERTY(EditDefaultsOnly, Category = PeriodicSpawn)
	float MinTimeBetweenSpawn = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = PeriodicSpawn)
	float MaxTimeBetweenSpawn = 30.f;

	UFUNCTION()
	void TimedSpawn();

public:	
	
	void GenerateSave();

	UFUNCTION()
	void PauseTimedSpawn();

	UFUNCTION()
	void UnPauseTimedSpawn();

	void Init(FVillageManagerLoadInfoStruct InLoadInfo);

	FStateUpdatedSignature OnStateUpdated;
	FVilligersUpdatedSignature OnVillagersUpdated;

	void AddVillagerToColony(AVillager* Villager);
	void AddWorkStationToColony(ABaseWorkStation* WorkStation);

	FVillageManagerLoadInfoStruct GetSaveInfo();

	TArray<AVillager*> GetAllVillagers() { return Villagers; }
	AVillager* GetWorkerAt(ABaseWorkStation* WorkStation);
	ABaseWorkStation* GetWorkPlaceFor(int WorkerID);
	UFUNCTION()
	void ManageEmployment(ABaseWorkStation* WorkStation, int WorkerIndex);
	ABaseWorkStation* GetFirstForConstructing();

	//---------------------CheatSection-----------------------------------
	friend class AGameplayModeBase;
};

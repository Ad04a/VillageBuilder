// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Headers/DataLinkable.h"
#include "Headers/StatAndTraitEnums.h"
#include "Headers/ItemInfo.h"
#include "Headers/Professions.h"
#include "Engine/DataTable.h"
#include "WorkSystem/BuildProjection.h"
#include "Components/BuildingClusterComponent.h"
#include "Components/StorageComponent.h"
#include "BaseWorkStation.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FBuildingStateSignature, ABaseWorkStation*, WorkStation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FConstructionStateSignature, bool, State, ABaseWorkStation*, WorkStation);

USTRUCT(BlueprintType)
struct FWorkStationData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText DisplayName;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EProfessions> Profession;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<ETrait>, float> TraitModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABaseWorkStation> ActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABuildProjection> BuildProjectionClass;
};

USTRUCT(BlueprintType)
struct FProfessionBehaviorData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterialInterface* Material;
};



USTRUCT(BlueprintType)
struct FWorkStationInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<AActor> WorkStationClass;

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	FBuildingClusterInfoStruct BuildingClusterInfo = FBuildingClusterInfoStruct();

	UPROPERTY()
	TMap<FIntPoint, FItemInfoStruct> InventoryInfo;

	UPROPERTY()
	int ID = -1;

	inline bool operator==(const FWorkStationInfoStruct& other) const
	{
		return (other.WorkStationClass == WorkStationClass) && (other.Transform.GetLocation() == Transform.GetLocation());
	}
	inline bool operator != (const FWorkStationInfoStruct& other) const
	{
		return !((other.WorkStationClass == WorkStationClass) && (other.Transform.GetLocation() == Transform.GetLocation()));
	}
};

UCLASS()
class VILLAGEBUILDER_API ABaseWorkStation : public AActor, public IDataLinkable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWorkStation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AActor* HiredVillager = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* StationDataTable;

	UPROPERTY(VisibleAnywhere)
	FText DisplayName;

	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EProfessions> Profession;

	UPROPERTY(VisibleAnywhere)
	TMap<TEnumAsByte<ETrait>, float> TraitModifiers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBuildingClusterComponent* BuildingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStorageComponent* StorageComponent = nullptr;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DataLink")
	void BreakDataLinks();
	virtual void BreakDataLinks_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DataLink")
	FText DisplayDataLinkText();
	virtual FText DisplayDataLinkText_Implementation();

	bool IsBuilt = false;
	bool IsConstructing = false;
	UFUNCTION()
	void SetIsBuilt(bool State);
	UFUNCTION()
	void SetIsConstructing(bool State);

public:	
	UPROPERTY(VisibleAnywhere, Category = Identification)
	unsigned int ID = -1;

	FConstructionStateSignature OnStartedConstruction;
	FBuildingStateSignature OnBuildingReady;
	FBrakeLinkSignature OnLinkBroken;

	void Init(FWorkStationInfoStruct InLoadInfo = FWorkStationInfoStruct());
	FWorkStationInfoStruct GetSaveInfo();
	void StartBuild();

	static ABaseWorkStation* ABaseWorkStation::CreateInstance(UObject* WorldContext, FWorkStationInfoStruct InLoadInfo = FWorkStationInfoStruct());

	FText GetName() { return DisplayName; }
	TMap<TEnumAsByte<ETrait>, float> GetModifiers() { return TraitModifiers; }
	EProfessions GetProfession() { return Profession; }
	bool GetIsBuilt() { return IsBuilt; }
	bool GetIsConstructing() { return IsConstructing; }
	class UStorageComponent* GetStorageComponent() { return StorageComponent; }
	class UBuildingClusterComponent* GetBuildingComponent() {return BuildingComponent ;	}

	//------------------CheatSection---------------
	void ForceBuild();
};

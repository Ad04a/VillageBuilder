// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Headers/Interactable.h"
#include "Headers/StatAndTraitEnums.h"
#include "Engine/DataTable.h"
#include "WorkSystem/BuildProjection.h"
#include "Components/BuildingClusterComponent.h"
#include "BaseWorkStation.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FBuildingStateSignature, ABaseWorkStation*, WorkStation);

USTRUCT(BlueprintType)
struct FWorkStationData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText DisplayName;

	UPROPERTY(EditAnywhere)
	FText ProfessionName;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<ETrait>, float> TraitModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABaseWorkStation> ActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABuildProjection> BuildProjectionClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBehaviorTree* BehaviorTree;
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
class VILLAGEBUILDER_API ABaseWorkStation : public AActor, public IInteractable
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
	FText ProfessionName;

	UPROPERTY(VisibleAnywhere)
	TMap<TEnumAsByte<ETrait>, float> TraitModifiers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBuildingClusterComponent* BuildingComponent = nullptr;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractRequest(class AVillager* InteractingVillager);
	virtual void InteractRequest_Implementation(class AVillager* InteractingVillager);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FText DisplayInteractText();
	virtual FText DisplayInteractText_Implementation();

	bool IsBuilt = false;
	bool IsConstructing = false;
	UFUNCTION()
	void SetIsBuilt(bool State);
	UFUNCTION()
	void SetIsConstructing(bool State);

public:	
	UPROPERTY(VisibleAnywhere, Category = Identification)
	unsigned int ID = -1;
	FBuildingStateSignature OnStartedConstruction;
	FBuildingStateSignature OnBuildingReady;

	void Init(FWorkStationInfoStruct InLoadInfo = FWorkStationInfoStruct());
	FWorkStationInfoStruct GetSaveInfo();

	static ABaseWorkStation* ABaseWorkStation::CreateInstance(UObject* WorldContext, FWorkStationInfoStruct InLoadInfo = FWorkStationInfoStruct());

	FText GetName() { return DisplayName; }
	float GetModifier(ETrait TraitName);
	FText GetProfessionName() { return ProfessionName; }
	bool GetIsBuilt() { return IsBuilt; }
	bool GetIsConstructing() { return IsConstructing; }
	void ForceBuild();
	class UBaseBuildingComponent* GetFirstBuildingComponent(); 


};

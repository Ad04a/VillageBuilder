// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Headers/Interactable.h"
#include "BuildingClusterComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FBuildingClusterStateSignature, bool, State);

USTRUCT(BlueprintType)
struct FBuildingClusterInfoStruct
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<int> PlacedIDs;

	UPROPERTY()
	bool bIsConstructing;

	inline bool operator==(const FBuildingClusterInfoStruct& other) const
	{
		return (other.PlacedIDs == PlacedIDs) && (other.bIsConstructing == bIsConstructing);
	}
	inline bool operator != (const FBuildingClusterInfoStruct& other) const
	{
		return !((other.PlacedIDs == PlacedIDs) && (other.bIsConstructing == bIsConstructing));
	}
};

UCLASS()
class VILLAGEBUILDER_API UBuildingClusterComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	int PlacedComponents = 0;
	int AllComponents = 0;
	bool bIsStarted = false;
	TArray<int> PlacedIDs;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* MainMaterial;

	UFUNCTION()
	void OnComponentPlaced(int ID, bool State);
public:
	void StartBuild();
	FBuildingClusterStateSignature OnBuildingFinisehd;
	FBuildingClusterStateSignature OnBuildStarted;
	void Init(FBuildingClusterInfoStruct InLoadInfo = FBuildingClusterInfoStruct());
	FBuildingClusterInfoStruct GetSaveInfo();
	TArray<class UBaseBuildingComponent*> GetBuildingComponents();
	class UBaseBuildingComponent* GetFirstBuildingComponent();
	void ForceBuild();
};

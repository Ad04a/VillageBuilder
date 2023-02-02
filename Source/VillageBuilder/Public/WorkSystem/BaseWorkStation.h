// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/VillageMayor.h"
#include "Headers/Interactable.h"
#include "Components/BuildingClusterComponent.h"
#include "BaseWorkStation.generated.h"

USTRUCT(BlueprintType)
struct FWorkStationData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText DisplayName;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<ETrait>, float> TraitModifiers;

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
	TMap<TEnumAsByte<ETrait>, float> TraitModifiers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBuildingClusterComponent* BuildingComponent = nullptr;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractRequest(class AVillageMayor* InteractingPlayer);
	virtual void InteractRequest_Implementation(class AVillageMayor* InteractingPlayer);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FText DisplayInteractText();
	virtual FText DisplayInteractText_Implementation();

public:	
	void ReleaseWorker();

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/SpawningItem.h"
#include "BuilderItem.generated.h"

USTRUCT(BlueprintType)
struct FBuilderData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ActorToSpawn;
};

UCLASS()
class VILLAGEBUILDER_API ABuilderItem : public ASpawningItem
{
	GENERATED_BODY()
private:
	bool bIsProjecting = false;

protected:
	virtual void Use(class AVillager* User, EItemActionType ActionType) override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnDrop() override;
	virtual void LoadFromDataTable() override;
	virtual void SetIsActive(bool State) override;
	virtual FVector GetSpawnLocation() override;
	virtual FRotator GetSpawnRotation() override;

	UPROPERTY(VisibleAnywhere)
	FName CurrentStationName = "";

public:
	UFUNCTION()
	void Init(FName StationName);

};

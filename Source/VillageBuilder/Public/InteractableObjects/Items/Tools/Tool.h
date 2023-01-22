// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObjects/Items/Item.h"
#include "Characters/Villager.h"
#include "Tool.generated.h"

USTRUCT(BlueprintType)
struct FToolData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseDamage;
};

UCLASS()
class VILLAGEBUILDER_API ATool : public AItem
{
	GENERATED_BODY()
	
private:
	AVillager* UsingVillager = nullptr;
	bool bIsCurrentlyUsed = false;
	TSet<AActor*> DamagedActors;

public:
	ATool();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void LoadFromDataTable() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tool )
	float BaseDamage;

public:
	virtual void Use(class AVillager* User, EItemActionType ActionType) override;

};

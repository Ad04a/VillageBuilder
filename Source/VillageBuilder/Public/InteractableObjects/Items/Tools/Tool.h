// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObjects/Items/Item.h"
#include "Tool.generated.h"

USTRUCT(BlueprintType)
struct FToolData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Durability;
};

UCLASS()
class VILLAGEBUILDER_API ATool : public AItem
{
	GENERATED_BODY()
	
public:
	ATool();

protected:

	virtual void BeginPlay() override;

	virtual void LoadFromDataTable() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tool )
	int Durability;

public:
	virtual void Use(class AVillager* User) override;

};

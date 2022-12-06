// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/Villager.h"
#include "Items/ItemSlotComponent.h"
#include "Item.generated.h"

UCLASS(Abstract, BlueprintType)
class VILLAGEBUILDER_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item, meta = (Multiline = true))
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	UStaticMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	float Weight;

	UPROPERTY()
	UItemSlotComponent* OwningItemSlot;

	
	virtual void Use(class AVillager* User) PURE_VIRTUAL(UItem, );

public:	

};

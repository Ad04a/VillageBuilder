// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/Villager.h"
#include "InteractableObjects/Items/ItemSlotComponent.h"
#include "InteractableObjects/Interactable.h"
#include "Item.generated.h"

UCLASS(BlueprintType)
class VILLAGEBUILDER_API AItem : public AActor, public IInteractable
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	FText InteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item, meta = (Multiline = true))
	FText Description;

	UPROPERTY(EditAnywhere)
	class USceneComponent* Root = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	float Weight;

	UPROPERTY()
	UItemSlotComponent* OwningItemSlot;

	virtual void Use(class AVillager* User) PURE_VIRTUAL(UItem, );

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractRequest(class AVillager* InteractingVillager);
	virtual void InteractRequest_Implementation(class AVillager* InteractingVillager);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FText DisplayInteractText();
	virtual FText DisplayInteractText_Implementation();

public:	

};

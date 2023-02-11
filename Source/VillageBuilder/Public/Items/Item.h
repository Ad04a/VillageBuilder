// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Headers/Interactable.h"
#include "Headers/ItemInfo.h"
#include "Headers/ItemActionEnums.h"
#include "Item.generated.h"


UCLASS(BlueprintType)
class VILLAGEBUILDER_API AItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void LoadFromDataTable();

	bool IsActive = false;
	AVillager* UsingVillager = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDataTable* MainDataTable = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDataTable* SecondaryDataTable = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	float Weight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FText DisplayName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item, meta = (Multiline = true))
	FText Description;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	TEnumAsByte<EItemType> ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	UAnimMontage* ItemAnimMontage;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void InteractRequest(class AVillager* InteractingVillager);
	virtual void InteractRequest_Implementation(class AVillager* InteractingVillager);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FText DisplayInteractText();
	virtual FText DisplayInteractText_Implementation();

public:

	UFUNCTION()
	EItemType GetItemType();

	UFUNCTION()
	virtual void SetIsActive(bool State) { IsActive = State; }

	UFUNCTION()
	virtual void Use(class AVillager* User, EItemActionType ActionType);

	UFUNCTION()
	void SetEnablePhysics(bool State);

	UFUNCTION()
	virtual FString SerializetemInfo() PURE_VIRTUAL(AItem::SerializetemInfo, return "";);

	UFUNCTION()
	virtual void OnDrop() { UsingVillager = nullptr; }

	UFUNCTION()
	UMaterialInterface* GetMaterial();

};

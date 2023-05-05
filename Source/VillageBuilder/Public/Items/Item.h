// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Headers/Interfaces/Interactable.h"
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
	bool bSaveAlone = true;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
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
	FIntPoint Slots;

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
	static AItem* CreateInstance(UObject* WorldContext, FItemInfoStruct InLoadInfo = FItemInfoStruct());
	static AItem* SpawnItem(UObject* WorldContext, TSubclassOf<AItem> SpecificClass);
	inline static unsigned int CurrentID = 0;

	unsigned int ID = -1;

	UFUNCTION()
	virtual FString Init(FItemInfoStruct InLoadInfo = FItemInfoStruct());

	UFUNCTION()
	virtual FItemInfoStruct GetSaveInfo();

	UFUNCTION()
	virtual FString SerializetemInfo();

	UFUNCTION()
	EItemType GetItemType();

	UFUNCTION()
	virtual void SetIsActive(bool State) { IsActive = State; }

	UFUNCTION()
	virtual void Use(class AVillager* User, EItemActionType ActionType);

	UFUNCTION()
	void SetEnablePhysics(bool State);

	UFUNCTION()
	bool GetSaveAlone();

	UFUNCTION()
	virtual void OnDrop() { UsingVillager = nullptr; }

	UFUNCTION()
	UMaterialInterface* GetMaterial();

	FIntPoint GetSlots() { return Slots; }

	class UDataTable* GetDataTable() { return MainDataTable; }

};

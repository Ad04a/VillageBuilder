// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Items/Item.h"
#include "ItemCarrierComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VILLAGEBUILDER_API UItemCarrierComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemCarrierComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Content)
	TMap<TSubclassOf<AItem>, int> Content;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItem(AItem* Item);

	virtual AItem* DropItem(TSubclassOf<AItem> ItemClass);

	void DropAllItems();

	TArray<TSubclassOf<AItem>> GetItemTypes();




		
};
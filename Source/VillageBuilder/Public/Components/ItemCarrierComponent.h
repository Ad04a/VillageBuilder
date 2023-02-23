// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "ItemCarrierComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VILLAGEBUILDER_API UItemCarrierComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemCarrierComponent();

protected:

	UPROPERTY(EditAnywhere, Category = Content)
	TMap<TSubclassOf<AItem>, int> Content;

public:	

	void AddItem(AItem* Item);

	virtual AItem* DropItem(TSubclassOf<AItem> ItemClass);

	void DropAllItems();

	TArray<TSubclassOf<AItem>> GetItemTypes();




		
};

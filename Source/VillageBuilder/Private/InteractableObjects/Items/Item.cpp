// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Items/Item.h"

#include "Characters/Villager.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	MovementComponent->ProjectileGravityScale = 1;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::InteractRequest_Implementation(class AActor* InteractingActor)
{
	AVillager* InteractingVillager = Cast<AVillager>(InteractingActor);
	//GetItemInfo();
	InteractingVillager->Equip(this);
	
}

FText AItem::DisplayInteractText_Implementation()
{
	return FText::FromString( "Pick up " + DisplayName.ToString());
}

EItemType AItem::GetItemType()
{
	return ItemType;
}

UProjectileMovementComponent* AItem::GetMovementComponent()
{
	return MovementComponent;
}

	/*a
fiteminfostruct aitem::getiteminfo()
{ 
	fiteminfostruct iteminfo;
	iteminfo.itemclass = getclass();
	ue_log(logtemp, error, text("aitem::getiteminfo %s"), *iteminfo.itemclass->getname());
	return iteminfo;
}*/


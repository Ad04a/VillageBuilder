// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

#include "Characters/VillageMayor.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	SetEnablePhysics(true);
	LoadFromDataTable();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem::LoadFromDataTable()
{	
	if (IsValid(MainDataTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AItem::LoadFromDataTable() IsValid(DataTable) == false from %s"), *GetClass()->GetName());
		return;
	}

	FItemData* ItemData = MainDataTable->FindRow<FItemData>(GetClass()->GetFName(), "");

	if (ItemData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AItem::LoadFromDataTable() ItemData == nullptr from %s"), *GetClass()->GetName());
		return;
	}

	Weight			= ItemData->Weight;
	DisplayName		= ItemData->DisplayName;
	Description		= ItemData->Description;
	ItemType		= ItemData->ItemType;
	ItemAnimMontage = ItemData->ItemAnimMontage;
}

void AItem::InteractRequest_Implementation(class AVillageMayor* InteractingPlayer)
{
	InteractingPlayer->Equip(this);	
}

void AItem::Use(AVillager* User, EItemActionType ActionType)
{
	UsingVillager = User;
	FText MyEnumValueText;
	UEnum::GetDisplayValueAsText(ActionType, MyEnumValueText);
	User->PlayItemAnimMontage(ItemAnimMontage,FName(MyEnumValueText.ToString()));
		
}

FText AItem::DisplayInteractText_Implementation()
{
	return FText::FromString( "Pick up " + DisplayName.ToString());
}

EItemType AItem::GetItemType()
{
	return ItemType;
}

void AItem::SetEnablePhysics(bool State)
{
	MeshComponent->SetSimulatePhysics(State);
	SetActorEnableCollision(State);
}

UMaterialInterface* AItem::GetMaterial()
{
	return MeshComponent->GetStaticMesh()->GetMaterial(0);
}


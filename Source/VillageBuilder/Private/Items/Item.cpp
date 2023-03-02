// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Characters/VillageMayor.h"

AItem* AItem::CreateInstance(UObject* WorldContext, FItemInfoStruct InLoadInfo)
{
	UWorld* World = WorldContext->GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AItem::CreateInstance IsValid(World) == false"));
		return nullptr;
	}
	if (InLoadInfo == FItemInfoStruct())
	{
		return nullptr;
	}
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AItem* Item = World->SpawnActor<AItem>(InLoadInfo.ItemClass, FVector(0, 0, 300), FRotator(0, 0, 0), Params);
	Item->Init(InLoadInfo);
	return Item;
}

AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
	MeshComponent->SetCollisionProfileName("BlockAll");
	
}

FString AItem::Init(FItemInfoStruct InLoadInfo)
{
	if (InLoadInfo == FItemInfoStruct())
	{
		return "";
	}
	SetActorTransform(InLoadInfo.Transform);
	return InLoadInfo.SerializedItem;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	SetEnablePhysics(true);
	LoadFromDataTable();
}

FString AItem::SerializetemInfo()
{
	return "";
}

FItemInfoStruct AItem::GetSaveInfo()
{
	FItemInfoStruct SaveInfo;
	SaveInfo.ItemClass      = GetClass();
	SaveInfo.SerializedItem = SerializetemInfo();
	SaveInfo.Transform		= GetActorTransform();
	return SaveInfo;
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

	Slots			= ItemData->Slots;
	DisplayName		= ItemData->DisplayName;
	Description		= ItemData->Description;
	ItemType		= ItemData->ItemType;
	ItemAnimMontage = ItemData->ItemAnimMontage;
}

void AItem::InteractRequest_Implementation(class AVillager* InteractingVillager)
{
	UsingVillager = InteractingVillager;
	InteractingVillager->PickUp(this);
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
	bSaveAlone = State;
	MeshComponent->SetSimulatePhysics(State);
	SetActorEnableCollision(State);
	if (State == true)
	{
		MeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);
		return;
	}
	MeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Ignore);
}

bool AItem::GetSaveAlone()
{
	return bSaveAlone;
}


UMaterialInterface* AItem::GetMaterial()
{
	return MeshComponent->GetStaticMesh()->GetMaterial(0);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Villager.h"
#include "Characters/VillageMayor.h"
#include "GameModes/GameplayModeBase.h"
#include "Components/StorageComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AVillager::AVillager()
{
	PrimaryActorTick.bCanEverTick = true;
	OnTakeAnyDamage.AddDynamic(this, &AVillager::RecieveDamage);
	Inventory = CreateDefaultSubobject<UStorageComponent>(TEXT("Iventory"));
}

void AVillager::Init(FVillagerLoadInfoStruct InLoadInfo, FString InName)
{
	bool bIsLoadingFromFile = false;
	//--------InitWithDataFromSaveFile--------
	if (InLoadInfo != FVillagerLoadInfoStruct())
	{
		Name      = InLoadInfo.Name;
		TraitsMap = InLoadInfo.TraitsMap;
		StatsMap  = InLoadInfo.StatsMap;
		ID		  = InLoadInfo.ID;
		SetActorTransform(InLoadInfo.Transform);
		AItem* Item = AItem::CreateInstance(this, InLoadInfo.HoldingItem);
		if (IsValid(Item) == true)
		{
			Equip(Item);
		}
		bIsLoadingFromFile = true;
	}
	Inventory->Init(InLoadInfo.InventoryInfo);
	if (InName != "")
	{
		Name = InName;
	}
	//------------LoadDataForMaps--------------
	if (IsValid(StatTraitDataTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AItem::LoadFromDataTable() IsValid(DataTable) == false from %s"));
		return;
	}

	FStatTraitData* StatTraitData = StatTraitDataTable->FindRow<FStatTraitData>(RollToRead, "");

	if (StatTraitData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AItem::LoadFromDataTable() ItemData == nullptr from %s"));
		return;
	}

	StatTraitRelation = StatTraitData->StatTraitRelation;
	if (bIsLoadingFromFile == true)
	{
		return;
	}
	TraitsMap		  = StatTraitData->TraitsMap;
	StatsMap		  = StatTraitData->StatsMap;

	//------------InitTraits--------------

	int PossibleLevel = TraitsCap; //depending on the current colony level
	TArray<TEnumAsByte<ETrait>> TraitList;
	TraitsMap.GetKeys(TraitList);
	for (TEnumAsByte<ETrait> TraitName : TraitList) {

		FTraitInfoStruct* Trait = TraitsMap.Find(TraitName);
		if (Trait == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("AVillager::Init::InitTraits IsValid(Trait) == false"));
			return;
		}
		Trait->Level = FMath::RandRange(1, PossibleLevel);
	}
	CalculateStats();
}

void AVillager::CalculateStats()
{
	//------------InitStats--------------
	TArray<TEnumAsByte<ETrait>> TraitList;
	TArray<TEnumAsByte<EStat>> StatList;

	StatTraitRelation.GetKeys(StatList);
	StatTraitRelation.GenerateValueArray(TraitList);

	for (int i = 0; i < StatList.Num(); i++) {

		FStatInfoStruct* Stat = StatsMap.Find(StatList[i]);
		if (Stat == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("AVillager::Init::InitStats IsValid(Stat) == false"));
			return;
		}
		FTraitInfoStruct* Trait = TraitsMap.Find(TraitList[i]);
		if (Trait == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("AVillager::Init::InitStats IsValid(Trait) == false"));
			return;
		}
		Stat->Max = Stat->Default + Trait->Level * Stat->PerLevel;
		Stat->Current = Stat->Max;
	}
}

FVillagerLoadInfoStruct AVillager::GetSaveInfo()
{
	FVillagerLoadInfoStruct SaveInfo;
	SaveInfo.Name	       = Name;
	SaveInfo.TraitsMap     = TraitsMap;
	SaveInfo.StatsMap      = StatsMap;
	SaveInfo.Transform     = GetActorTransform();
	SaveInfo.ID			   = ID;
	SaveInfo.InventoryInfo = Inventory->GetSaveInfo();
	if (ItemSlot != nullptr)
	{
		SaveInfo.HoldingItem = ItemSlot->GetSaveInfo();
	}
	return SaveInfo;
}

void AVillager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FStatInfoStruct* Health = StatsMap.Find(EStat::Health);
	if (Health->Current == 0) {
		Die();
	}

	StatDepletion += DeltaTime;
	if (StatDepletion < StatDepletionInterval) {
		return;
	}

	FStatInfoStruct* Thirst = StatsMap.Find(EStat::Thirst);
	AddStatValue(EStat::Thirst, Thirst->ChangeValue);

	if (Thirst->Current == 0) {
		AddStatValue(EStat::Health, Health->Max * -0.05);
	}

	FStatInfoStruct* Hunger = StatsMap.Find(EStat::Hunger);
	AddStatValue(EStat::Hunger, Hunger->ChangeValue);

	if (Hunger->Current == 0) {
		AddStatValue(EStat::Health, Health->Max * -0.02);
	}

	FStatInfoStruct* Energy = StatsMap.Find(EStat::Energy);
	AddStatValue(EStat::Energy, Energy->ChangeValue);

	if (Energy->Current == 0) {
		AddStatValue(EStat::Health, Health->Max * -0.01);
	}

	if (Hunger->Current > Hunger->Max * SaturationForPassiveHealing && 
		Thirst->Current > Thirst->Max * SaturationForPassiveHealing && 
		Health->Current < Health->Max) {

		AddStatValue(EStat::Health, Health->ChangeValue);
	}

	StatDepletion = 0;
	
}

void AVillager::RecieveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	AddStatValue(EStat::Health, -Damage);
}

void AVillager::Die()
{
	OnDeath.Broadcast(this);
	if (InteractingWith == nullptr)
	{
		return;
	}
	InteractRequest_Implementation(InteractingWith);
}

void AVillager::Equip(AActor* ItemToEquip)
{
	AItem* NewItem = Cast<AItem>(ItemToEquip);
	if (IsValid(NewItem) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::Equip IsValid(NewItem) == false"));
		return;
	}
	if (CanEquip() == false)
	{
		if (Inventory->PlaceItem(NewItem) == false)
		{
			if (Inventory->PlaceItem(ItemSlot) == false)
			{
				return;
			}
		}
	}
	NewItem->SetEnablePhysics(false);
	ItemToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_l_Socket"));
	ItemSlot = NewItem;
}

void AVillager::DropItem()
{
	if (IsValid(ItemSlot) == false)
	{
		return;
	}
	ItemSlot->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	ItemSlot->SetEnablePhysics(true);
	ItemSlot->OnDrop();
	ItemSlot = nullptr;
}


void AVillager::UseItem(EItemActionType ActionType)
{
	if (bCanUseItems == false)
	{
		return;
	}
	if (IsValid(ItemSlot) == false) {
		return;
	}
	ItemSlot->Use(this, ActionType);
}

void AVillager::RecieveXP(ETrait, int XPAmount)
{


}

void AVillager::AcknowledgeWidgetBinding()
{
	for (EStat Stat : TEnumRange<EStat>())
	{
		FStatInfoStruct* StatStruct = StatsMap.Find(Stat);
		OnStatUpdated.Broadcast(Stat, StatStruct->Current, StatStruct->Max);
	}

}

void AVillager::UpdateMovement(float MoveForwardValue, float MoveRightValue)
{
	if ( InputEnabled() == false || bIsMovementEnabled == false)
	{
		return;
	}

	if (MoveForwardValue != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), MoveForwardValue);
	}
	if (MoveRightValue != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), MoveRightValue);
	}
}

void AVillager::TurnAtRate(float Rate)
{
	if (InputEnabled() == false || bIsRotationEnabled == false)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::TurnAtRate IsValid(World) == false"));
		return;
	}

	//Functionality to move slower with lower energy

	AddControllerYawInput(Rate * World->GetDeltaSeconds());
}

void AVillager::LookUpAtRate(float Rate)
{
	if (InputEnabled() == false || bIsRotationEnabled == false)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::LookUpAtRate IsValid(World) == false"));
		return;
	}

	//Functionality to turn slower with lower energy


	AddControllerPitchInput(Rate *Energy * World->GetDeltaSeconds());
	
}

void AVillager::PlayItemAnimMontage(UAnimMontage* AnimMontage, FName StartSectionName)
{
	if (IsValid(AnimMontage) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::PlayItemAnimMontage IsValid(AnimMontage) == false"));
		return;
	}
	if (IsValid(GetMesh()) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::PlayItemAnimMontage IsValid(GetMesh()) == false"));
		return;
	}
	if (IsValid(GetMesh()->GetAnimInstance()) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::PlayItemAnimMontage IsValid(GetMesh()->GetAnimInstance()) == false"));
		return;
	}
	if (GetMesh()->GetAnimInstance()->Montage_IsActive(NULL))
	{
		return;
	}
	PlayAnimMontage(AnimMontage, 1, StartSectionName);
}



void AVillager::AddStatValue(EStat StatName, float InValue)
{
	FStatInfoStruct* Stat = StatsMap.Find(StatName);
	if (Stat == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AVillager::AddStatValue IsValid(Stat) == false"));
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("UStatsAndTraitsVisualInfo::PassStatUpdate: %s - %f / %f"), *UEnum::GetValueAsString(StatName), Stat->Current, InValue);
	float NewValue = FMath::Clamp(Stat->Current + InValue, 0, Stat->Max);
	if (NewValue == Stat->Current)
	{
		return;
	}
	Stat->Current = NewValue;
	OnStatUpdated.Broadcast(StatName,Stat->Current, Stat->Max);
}

int AVillager::GetTrait(ETrait TraitName)
{
	FTraitInfoStruct* Trait = TraitsMap.Find(TraitName);
	if (Trait == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AVillager::GetTrait IsValid(Trait) == false"));
		return 0;
	}

	return Trait->Level;
}

void AVillager::InteractRequest_Implementation(class AVillager* InteractingVillager)
{
	AVillageMayor* InteractingPlayer = Cast<AVillageMayor>(InteractingVillager);
	if (IsValid(InteractingPlayer) == false)
	{
		return;
	}
	InteractingPlayer->ToggleTraitsMenu(this);
	if (InteractingWith == nullptr)
	{
		InteractingWith = InteractingPlayer;
		return;
	}
	InteractingWith = nullptr;
}

FText AVillager::DisplayInteractText_Implementation()
{
	return FText::FromString( "Talk with " + Name);//Add name variable
}

EItemType AVillager::GetEquipItemType()
{
	if (ItemSlot == nullptr)
	{
		return EItemType::Default;
	}
	return ItemSlot->GetItemType();
}

ABaseWorkStation* AVillager::GetWorkStation()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::GetWorkStation() IsValid(World) == false"));
		return nullptr;
	}

	AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillager::GetWorkStation() IsValid(GameMode) == false"));
		return nullptr;
	}

	AVillageManager* Village = GameMode->GetCurrentVillage(this);
	if (IsValid(Village) == false) {
		UE_LOG(LogTemp, Error, TEXT("AVillager::GetWorkStation() IsValid(Village) == false"));
		return nullptr;
	}

	return Village->GetWorkPlaceFor(ID);
}
FText AVillager::GetProfession()
{
	if (GetWorkStation() == nullptr)
	{
		return FText::FromString("Unemployeed");
	} 
	return GetWorkStation()->GetProfessionName();
}

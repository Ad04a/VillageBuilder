// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Villager.h"
#include "Characters/VillageMayor.h"



// Sets default values
AVillager::AVillager()
{
	PrimaryActorTick.bCanEverTick = true;
	OnTakeAnyDamage.AddDynamic(this, &AVillager::RecieveDamage);
}

void AVillager::Init(FLoadInfoStruct InLoadInfo)
{
	//--------InitWithDataFromSaveFile--------
	if (InLoadInfo != FLoadInfoStruct())
	{
		//ItemSlots = InLoadInfo.ItemSlots;
		TraitsMap = InLoadInfo.TraitsMap;
		StatsMap = InLoadInfo.StatsMap;
		SetActorTransform(InLoadInfo.Transform);
		return;
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

	TraitsMap		  = StatTraitData->TraitsMap;
	StatsMap		  = StatTraitData->StatsMap;
	StatTraitRelation = StatTraitData->StatTraitRelation;
	

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

	//------------InitStats--------------

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

FLoadInfoStruct AVillager::GetSaveInfo()
{
	FLoadInfoStruct SaveInfo;
	//SaveInfo.ItemSlots = ItemSlots;
	SaveInfo.TraitsMap = TraitsMap;
	SaveInfo.StatsMap     = StatsMap;
	SaveInfo.Transform     = GetActorTransform();

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

	if (Hunger->Current > Hunger->Max * SaturationForPassiveHealing && Thirst->Current > Thirst->Max * SaturationForPassiveHealing) {

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
	UE_LOG(LogTemp, Error, TEXT("Villager is dead"));

}

void AVillager::Equip(AActor* ItemToEquip)
{
	//
	AItem* NewItem = Cast<AItem>(ItemToEquip);
	if (IsValid(ItemSlot) == false) {
		NewItem->SetEnablePhysics(false);
		ItemToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_l_Socket"));
		ItemSlot = NewItem;
		return;
	}

}

void AVillager::DropItem()
{
	if (IsValid(ItemSlot) == false)
	{
		return;
	}
	ItemSlot->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	ItemSlot->SetEnablePhysics(true);
	ItemSlot = nullptr;
}


void AVillager::UseItem(EItemActionType ActionType)
{
	if (IsValid(ItemSlot) == false) {
		return;
	}
	ItemSlot->Use(this, ActionType);
}

void AVillager::RecieveXP(ETrait, int XPAmount)
{


}

void AVillager::AssignJob()
{
}

void AVillager::AcknowledgeWidgetBinding()
{
	AddStatValue(EStat::Hunger, 0);
	AddStatValue(EStat::Energy, 0);
	AddStatValue(EStat::Thirst, 0);
	AddStatValue(EStat::Health, 0);

}

void AVillager::UpdateMovement(float MoveForwardValue, float MoveRightValue)
{
	if ( InputEnabled() == false || IsMovementEnabled == false)
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
	if (InputEnabled() == false || IsRotationEnabled == false)
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
	if (InputEnabled() == false || IsRotationEnabled == false)
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
	
	Stat->Current = FMath::Clamp(Stat->Current+InValue, 0, Stat->Max);

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

void AVillager::InteractRequest_Implementation(class AActor* InteractingActor)
{
	AVillageMayor* InteractingPlayer = Cast<AVillageMayor>(InteractingActor);
	if (IsValid(InteractingPlayer) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::InteractRequest_Implementation IsValid(InteractingVillager) == false"));
		return;
	}
	InteractingPlayer->ToggleTraitsMenu(this);
	InteractingPlayer->IsInteracting = !InteractingPlayer->IsInteracting;
}

FText AVillager::DisplayInteractText_Implementation()
{
	return FText::FromString( "Talk with Villager" );//Add name variable
}

EItemType AVillager::GetEquipItemType()
{
	if (ItemSlot == nullptr)
	{
		return EItemType::Default;
	}
	return ItemSlot->GetItemType();
}

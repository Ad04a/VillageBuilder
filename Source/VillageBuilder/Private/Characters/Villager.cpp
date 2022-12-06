// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Villager.h"



// Sets default values
AVillager::AVillager()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); 
	CameraComponent->bUsePawnControlRotation = true;
}

void AVillager::BeginPlay()
{
	Super::BeginPlay();
}

void AVillager::Init()
{
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

void AVillager::Load(FLoadInfoStruct InLoadInfo)
{
	StatsMap       = InLoadInfo.StatsMap;
	TraitsMap      = InLoadInfo.TraitsMap;
	SetActorTransform(InLoadInfo.Position);
}

FLoadInfoStruct AVillager::SaveInfo()
{
	FLoadInfoStruct SaveInfo;
	SaveInfo.StatsMap     = StatsMap;
	SaveInfo.TraitsMap    = TraitsMap;
	SaveInfo.Position     = GetActorTransform();

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
	if (StatDepletion >= StatDepletionInterval) {

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

	 

}

void AVillager::Die()
{


}

void AVillager::RecieveXP(ETrait, int XPAmount)
{


}

void AVillager::AssignJob()
{
}

void AVillager::AcknowledgeStatWidgetBinding()
{
	AddStatValue(EStat::Hunger, 0);
	AddStatValue(EStat::Energy, 0);
	AddStatValue(EStat::Thirst, 0);
	AddStatValue(EStat::Health, 0);

}




void AVillager::SetIsMovementEnabled(bool State)
{
	IsMovementEnabled = State;
}

void AVillager::SetIsRotationEnabled(bool State)
{
	IsRotationEnabled = State;
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

void AVillager::AddStatValue(EStat StatName, float InValue)
{

	FStatInfoStruct* Stat = StatsMap.Find(StatName);
	if (Stat == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AVillager::AddStatValue IsValid(Stat) == false"));
		return;
	}
	
	Stat->Current = FMath::Clamp(Stat->Current+InValue, 0, Stat->Max);

	FStatUpdatedSignature* DelegateToUpdate = GetDelegateToUpdate(StatName);
	if (DelegateToUpdate == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AVillager::AddStatValue IsValid(DelegateToUpdate) == false"));
		return;
	}
	DelegateToUpdate->Broadcast(Stat->Current / Stat->Max);
}

FStatUpdatedSignature* AVillager::GetDelegateToUpdate(EStat StatName)
{
	switch (StatName)
	{
		case EStat::Energy :
			return &OnEnergyUpdated;

		case EStat::Health :
			return &OnHealthUpdated;

		case EStat::Hunger :
			return &OnHungerUpdated;

		case EStat::Thirst :
			return &OnThirstUpdated;

		default: return nullptr;
	}
}
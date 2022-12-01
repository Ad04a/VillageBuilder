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

	int Hunger, Thirst, Energy = 0;

	StatDepletion += DeltaTime;
	if (StatDepletion >= StatDepletionInterval) {

		Hunger = StatsMap.Find(EStat::Hunger)->Current;
		SetStat(EStat::Hunger, Hunger + StatsMap.Find(EStat::Hunger)->ChangeValue, OnHungerUpdated);

		Thirst = StatsMap.Find(EStat::Thirst)->Current;
		SetStat(EStat::Thirst, Thirst + StatsMap.Find(EStat::Thirst)->ChangeValue, OnThirstUpdated);

		Energy = StatsMap.Find(EStat::Energy)->Current;
		SetStat(EStat::Energy, Energy + StatsMap.Find(EStat::Energy)->ChangeValue, OnEnergyUpdated);

		StatDepletion = 0;
	}

	 

}

void AVillager::RecieveXP(ETrait, int XPAmount)
{


}

void AVillager::AssignJob()
{
}

void AVillager::AcknowledgeStatWidgetBinding()
{
	SetStat(EStat::Hunger, StatsMap.Find(EStat::Hunger)->Current, OnHungerUpdated);
	SetStat(EStat::Energy, StatsMap.Find(EStat::Energy)->Current, OnEnergyUpdated);
	SetStat(EStat::Thirst, StatsMap.Find(EStat::Thirst)->Current, OnThirstUpdated);
	SetStat(EStat::Health, StatsMap.Find(EStat::Health)->Current, OnHealthUpdated);

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

void AVillager::SetStat(EStat StatName, int InValue, FStatUpdatedSignature DelegateToUpdate) 
{

	FStatInfoStruct* Stat = StatsMap.Find(StatName);
	if (Stat == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AVillager::Init::InitStats IsValid(Stat) == false"));
		return;
	}
	if (InValue < 0)
	{
		Stat->Current = FMath::Max(InValue, 0);
	}
	else if(InValue > Stat->Max)
	{
		Stat->Current = FMath::Max(InValue, Stat->Max);
	}
	else
	{
		Stat->Current = InValue;
	}

	float Current = Stat->Current;
	float Max = Stat->Max;
	DelegateToUpdate.Broadcast(Current / Max);
}


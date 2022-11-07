// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager.h"



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
	TSet<FString> Stats;

	Stats.Add("Health");
	Stats.Add("Hunger");
	AdditionTraitStatRelation.Add(FString("Vitality"), Stats);
	Stats.Empty();

	Stats.Add("Energy");
	Stats.Add("Thirst");
	AdditionTraitStatRelation.Add(FString("Endurance"), Stats);
	Stats.Empty();

	Stats.Add("Energy");
	DeplentionTraitStatRelation.Add(FString("Agility"), Stats);
	Stats.Empty();

	Stats.Add("Hunger");
	Stats.Add("Thirst");
	DeplentionTraitStatRelation.Add(FString("Survavabilty"), Stats);
	Stats.Empty();
	
}

void AVillager::Load(FLoadInfoStruct InLoadInfo)
{
	StatsMap       = InLoadInfo.StatsMap;
	TraitsMap      = InLoadInfo.TraitsMap;
	CurrentLevel   = InLoadInfo.CurrentLevel;
	CurrentXp      = InLoadInfo.CurrentXP;
	SetActorLocation(InLoadInfo.Position);
}

FLoadInfoStruct AVillager::SaveInfo()
{
	FLoadInfoStruct LoadInfo;
	LoadInfo.StatsMap     = StatsMap;
	LoadInfo.TraitsMap    = TraitsMap;
	LoadInfo.CurrentLevel = CurrentLevel;
	LoadInfo.CurrentXP    = CurrentXp;
	LoadInfo.Position     = GetActorLocation();

	return LoadInfo;
}

void AVillager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVillager::LevelUp()
{
	CurrentLevel++;
	//LevelUp 3 traits according to job info or choose 3 if Player leveled up
	CalculateStats();
}

void AVillager::RecieveXP(int XPAmount)
{
	if (CurrentLevel >= LevelCap) {
		return;
	}

	CurrentXp += XPAmount;

	if (CurrentXp >= CurrentLevel * NeededXpPerLevel) {

		LevelUp();
		CurrentXp -= CurrentLevel * NeededXpPerLevel;
	}

}

void AVillager::AssignJob()
{
}


void AVillager::CalculateStats()
{

	for (TPair<FString, TSet<FString>> Relation : AdditionTraitStatRelation) {

		FTraitInfoStruct* TraitInfo = TraitsMap.Find(Relation.Key);
		if (TraitInfo == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("AVillager::CalculateStats Trait %s not found"), *Relation.Key);
			return;
		}
		int TraitValue = TraitInfo->Value;

		for (FString Stat : Relation.Value) {

			FStatStruct* StatInfo = StatsMap.Find(Stat);
			if (StatInfo == nullptr) {
				UE_LOG(LogTemp, Error, TEXT("AVillager::CalculateStats For Trait %s Stat %s not found"), *Relation.Key, *Stat);
				return
			}
			StatInfo->Max += (StatInfo->TicksToDecay - StatInfo->Starting) / (TraitValue + LevelCap-2);
			StatInfo->Current = StatInfo->Max;
		}
	}

	for (TPair<FString, TSet<FString>> Relation : DeplentionTraitStatRelation) {

		FTraitInfoStruct* TraitInfo = TraitsMap.Find(Relation.Key);
		if (TraitInfo == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("AVillager::CalculateStats Trait %s not found"), *Relation.Key);
			return;
		}
		int TraitValue = TraitInfo->Value;

		for (FString Stat : Relation.Value) {

			FStatStruct* StatInfo = StatsMap.Find(Stat);
			if (StatInfo == nullptr) {
				UE_LOG(LogTemp, Error, TEXT("AVillager::CalculateStats For Trait %s Stat %s not found"), *Relation.Key, *Stat);
				return
			}

			StatInfo->DepletionRate = (StatInfo->Starting) / ((TraitValue/4)*(TraitValue/4) + 4);
		}
	}


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

	FStatStruct* EnergyStat = StatsMap.Find("Energy");
	if (EnergyStat == nullptr) {

		UE_LOG(LogTemp, Error, TEXT("AVillager::TurnAtRate Stat 'Energy' not found"));
		return;
	}

	float Energy = EnergyStat->Current / EnergyStat->Max;

	AddControllerYawInput(Rate*Energy * World->GetDeltaSeconds());
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

	FStatStruct* EnergyStat = StatsMap.Find("Energy");
	if (EnergyStat == nullptr) {

		UE_LOG(LogTemp, Error, TEXT("AVillager::LookUpAtRate Stat 'Energy' not found"));
		return;
	}

	float Energy  = EnergyStat->Current / EnergyStat->Max;

	AddControllerPitchInput(Rate *Energy * World->GetDeltaSeconds());
	
}



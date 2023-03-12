// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SpawningGridComponent.h"
#include "Characters/Villager.h"

// Sets default values for this component's properties
USpawningGridComponent::USpawningGridComponent()
{
	PrimaryComponentTick.bCanEverTick = true; 
}

void USpawningGridComponent::Init(FVector InLocation, float InEnableRadius, float InDisableRadius)
{
	SetWorldLocation(InLocation);
	EnableRadius  = InEnableRadius;
	DisableRadius = InDisableRadius;

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("USpawningGridComponent::Init IsValid(World) == false"));
		return;
	}
	USignificanceManager* SignificanceManager = FSignificanceManagerModule::Get(World);
	if (IsValid(SignificanceManager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("USpawningGridComponent::Init IsValid(SignificanceManager) == false"));
		return;
	}
	auto SignificanceFunction = [&](USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint)->float
	{
		return CalculateSignificance(ObjectInfo, Viewpoint);
	};

	auto PostSignificanceFunction = [&](USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Signifcance, bool bFinal)
	{
		PostSignificanceCalculation(ObjectInfo, OldSignificance, Signifcance, bFinal);
	};

	SignificanceManager->RegisterObject(this, TEXT("AnimalSpawner"), SignificanceFunction, USignificanceManager::EPostSignificanceType::Sequential, PostSignificanceFunction);
}

void USpawningGridComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USpawningGridComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USpawningGridComponent::CaptureSpawn()
{
	if (bIsActive == false)
	{
		return;
	}
	OnSpawnInitiated.Broadcast(GetComponentLocation());
}

float USpawningGridComponent::CalculateSignificance(USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint)
{
	USpawningGridComponent* Spawner = Cast<USpawningGridComponent>(ObjectInfo->GetObject());
	if (IsValid(Spawner) == false)
	{
		return 0;
	}
	float Distance = (Spawner->GetComponentLocation() - Viewpoint.GetLocation()).Size();
	if (Distance < DisableRadius)
	{
		return 0;
	}
	if (Distance < EnableRadius)
	{
		return 1;
	}
	return 0;
}

void USpawningGridComponent::PostSignificanceCalculation(USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Signifcance, bool bFinal)
{
	USpawningGridComponent* Spawner = Cast<USpawningGridComponent>(ObjectInfo->GetObject());
	if (IsValid(Spawner) == false)
	{
		return;
	}
	if (Signifcance == 1)
	{
		Spawner->SetIsActive(true);
		return;
	}
	Spawner->SetIsActive(false);
}

void USpawningGridComponent::SetIsActive(bool State)
{
	bIsActive = State;
	SetComponentTickEnabled(State);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animal.h"
#include "Components/ItemCarrierComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAnimal::AAnimal()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ItemCarrierComponent = CreateDefaultSubobject<UItemCarrierComponent>(TEXT("ItemCarriage"));
	OnTakeAnyDamage.AddDynamic(this, &AAnimal::OnDamageTaken);
}

void AAnimal::Init(float InLifeTime, float InDespawnDistance)
{
	LifeTime = InLifeTime;
	DespawnDistance = InDespawnDistance;
}

// Called when the game starts or when spawned
void AAnimal::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AAnimal::BeginPlay IsValid(World) == false"));
		return;
	}
	USignificanceManager* SignificanceManager = FSignificanceManagerModule::Get(World);
	if (IsValid(SignificanceManager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AAnimal::BeginPlay IsValid(SignificanceManager) == false"));
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

	SignificanceManager->RegisterObject(this, TEXT("Animal"), SignificanceFunction, USignificanceManager::EPostSignificanceType::Sequential, PostSignificanceFunction);
}

// Called every frame
void AAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentLifeTime += DeltaTime;
	if (CurrentLifeTime < LifeTime)
	{
		return;
	}
	Disable();
}

void AAnimal::Die()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AAnimal::Die IsValid(World) == false"));
		return;
	}
	USignificanceManager* SignificanceManager = FSignificanceManagerModule::Get(World);
	if (IsValid(SignificanceManager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AAnimal::Die IsValid(SignificanceManager) == false"));
		return;
	}

	SignificanceManager->UnregisterObject(this);
	ItemCarrierComponent->DropAllItems();
	OnStateChanged.Broadcast(this, EAIState::Dead);
	Destroy();
}

void AAnimal::OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	if (Health <= 0)
	{
		Die();
	}
}


float AAnimal::CalculateSignificance(USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint)
{
	AAnimal* Animal = Cast<AAnimal>(ObjectInfo->GetObject());
	if (IsValid(Animal) == false)
	{
		return 1;
	}
	float Distance = (Animal->GetActorLocation() - Viewpoint.GetLocation()).Size();
	if (Distance > DespawnDistance)
	{
		return 0;
	}
	return 1;
}

void AAnimal::PostSignificanceCalculation(USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Signifcance, bool bFinal)
{
	AAnimal* Animal = Cast<AAnimal>(ObjectInfo->GetObject());
	if (IsValid(Animal) == false)
	{
		return;
	}
	if (Signifcance == 1)
	{
		Animal->Activate();
		return;
	}
	Animal->Disable();
}

void AAnimal::Activate()
{
	GetCharacterMovement()->SetComponentTickEnabled(true);
	SetActorTickEnabled(true);
	bIsAcitve = true;
	CurrentLifeTime = 0;
	OnStateChanged.Broadcast(this, EAIState::Active);
}

void AAnimal::Disable()
{
	GetCharacterMovement()->SetComponentTickEnabled(false);
	SetActorTickEnabled(false);
	bIsAcitve = false;
	OnStateChanged.Broadcast(this, EAIState::Disabled);
}
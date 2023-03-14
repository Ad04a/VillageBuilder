// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AnimalSpawner.h"
#include "Components/SpawningGridComponent.h"
#include "Characters/Animal.h"
#include "Components/BoxComponent.h"

// Sets default values
AAnimalSpawner::AAnimalSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAnimalSpawner::Init(FAnimalSpawnerInfoStruct InLoadInfo)
{
	CurrentSpawnTime = InLoadInfo.CurrentSpawnTime;

	int i = 0;
	 
	for (FAnimalInfoStruct AnimalInfo : InLoadInfo.Animals)
	{
		i++;
		SpawnAnimal(FVector(50000, 50000, 50000))->Init(LifeTime, DisableDistance, AnimalInfo);
	}
	for (; i < MaxAnimals; i++)
	{
		SpawnAnimal(FVector(50000, 50000, 50000));
	}
}

FAnimalSpawnerInfoStruct AAnimalSpawner::GetSaveInfo()
{
	FAnimalSpawnerInfoStruct SaveInfo;
	SaveInfo.CurrentSpawnTime = CurrentSpawnTime;
	for (AAnimal* Animal : ActiveAnimals)
	{
		SaveInfo.Animals.Add(Animal->GetSaveInfo());
	}
	return SaveInfo;
}

// Called when the game starts or when spawned
void AAnimalSpawner::BeginPlay()
{
	Super::BeginPlay();
	if (EndX < StartX)
	{
		int Swap = StartX;
		StartX = EndX;
		EndX = Swap;
	}
	if (EndY < StartY)
	{
		int Swap = StartY;
		StartY = EndY;
		EndY = Swap;
	}
	USpawningGridComponent* NewGridElement = nullptr;
	for (int Y = StartY; Y < EndY; Y += SpawnRadius * 2)
	{
		for (int X = StartX; X < EndX; X += SpawnRadius * 2)
		{
			NewGridElement = NewObject<USpawningGridComponent>(this);
			if (IsValid(NewGridElement) == false)
			{
				UE_LOG(LogTemp, Warning, TEXT("AAnimalSpawner::BeginPlay IsValid(NewGridElement) == false"));
			}
			NewGridElement->RegisterComponent();
			NewGridElement->Init(FVector(X, Y, GetActorLocation().Z), EnableRadius, DisableRadius);
			NewGridElement->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
			NewGridElement->OnSpawnInitiated.AddDynamic(this, &AAnimalSpawner::RegisterSpawnRequest);
			OnSpawnEmited.AddDynamic(NewGridElement, &USpawningGridComponent::CaptureSpawn);
		}

	}
}

AAnimal* AAnimalSpawner::SpawnAnimal(FVector OriginLocation)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AAnimalSpawner::SpawnAnimal IsValid(World) == false"));
		return nullptr;
	}
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FVector Location = FMath::VRand();
	Location *= FMath::RandRange(0.f, SpawnRadius * 1.41f);
	Location += OriginLocation;
	int AnimlIndex = FMath::RandRange(0, AnimalTypes.Num()-1);
	AAnimal* Animal = World->SpawnActor<AAnimal>(AnimalTypes[AnimlIndex], Location, FRotator(0, FMath::RandRange(-180,180), 0), Params);
	Animal->OnStateChanged.AddDynamic(this, &AAnimalSpawner::RegisterAnimalState);
	Animal->Init(LifeTime, DisableDistance);
	DisabledAnimals.Add(Animal);
	return Animal;
}

void AAnimalSpawner::RegisterAnimalState(APawn* ControlledPawn, EAIState State)
{
	AAnimal* Animal = Cast<AAnimal>(ControlledPawn);
	if (IsValid(Animal) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("AAnimalSpawner::RegisterAnimalState IsValid(Animal) == false"));
		return;
	}
	if (State == EAIState::Active)
	{
		DisabledAnimals.Contains(Animal) ? DisabledAnimals.Remove(Animal) : 1;
		ActiveAnimals.Contains(Animal) ? 1 : ActiveAnimals.Add(Animal);
		
		return;
	}
	if (State == EAIState::Disabled)
	{
		ActiveAnimals.Contains(Animal) ? ActiveAnimals.Remove(Animal) : 1;
		DisabledAnimals.Contains(Animal) ? 1 : DisabledAnimals.Add(Animal);
		return;
	}
	if (State == EAIState::Dead)
	{
		Animal->OnStateChanged.RemoveDynamic(this, &AAnimalSpawner::RegisterAnimalState);
		ActiveAnimals.Contains(Animal) ? ActiveAnimals.Remove(Animal) : 1;
		DisabledAnimals.Contains(Animal) ? DisabledAnimals.Remove(Animal) : 1;
		return;
	}
}

void AAnimalSpawner::RegisterSpawnRequest(FVector OriginLocation)
{
	if (ActiveAnimals.Num() >= MaxAnimals)
	{
		return;
	}
	if (ActiveAnimals.Num() + DisabledAnimals.Num() < MaxAnimals)
	{
		SpawnAnimal(OriginLocation);		
	}
	if (DisabledAnimals.IsEmpty() == true)
	{
		return;
	}
	FVector Location = FMath::VRand();
	Location *= FMath::RandRange(0.f, SpawnRadius * 1.41f);
	Location += OriginLocation;
	DisabledAnimals[0]->SetActorLocation(Location);

}

// Called every frame
void AAnimalSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentSpawnTime += DeltaTime;
	if (CurrentSpawnTime < SpawnTime)
	{
		return;
	}
	CurrentSpawnTime = 0;
	OnSpawnEmited.Broadcast();
}


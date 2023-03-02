// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BuilderItem.h"
#include "GameModes/GameplayModeBase.h"
#include "DataTransfers/DataLink.h"

#include "Kismet/GameplayStatics.h"

ABuilderItem::ABuilderItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuilderItem::BindProjectionToPlayer(FName StationName)
{
	CurrentStationName = StationName;
	LoadFromDataTable();
	SpawnProjection();
}

void ABuilderItem::Use(class AVillager* User, EItemActionType ActionType)
{
	UsingVillager = User;
	if (CurrentProjection == nullptr)
	{
		UDataLink::CreateDataLink(UsingVillager, this);
		return;
	}
	if (CurrentProjection->GetIsValid() == false && EItemActionType::Primary)
	{
		return;
	}
	Super::Use(User, ActionType);
	
}

void ABuilderItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentProjection == nullptr)
	{
		return;
	}
	AVillageMayor* Mayor = Cast<AVillageMayor>(UsingVillager);
	if (IsValid(Mayor) == false)
	{
		return;
	}
	FVector StartTrace = Mayor->GetCameraComponent()->GetComponentLocation();
	FVector EndTrace = Mayor->GetCameraComponent()->GetForwardVector() * Reach + StartTrace;
	FVector NewLocation = FVector(EndTrace.X, EndTrace.Y, 0);
	
	CurrentProjection->SetActorLocation(NewLocation);
}

void ABuilderItem::SetIsActive(bool State)
{
	IsActive = State;
	if (State == false)
	{
		CurrentProjection->Destroy();
		CurrentProjection = nullptr;
		return;
	}

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ABuilderItem::SetIsActive IsValid(World) == false"));
		return;
	}

	AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("ABuilderItem::SetIsActive IsValid(GameMode) == false"));
		return;
	}

	AVillageManager* Village = GameMode->GetCurrentVillage(this);
	if (IsValid(Village) == false) {
		UE_LOG(LogTemp, Error, TEXT("ABuilderItem::SetIsActive IsValid(Village) == false"));
		return;
	}

	ABaseWorkStation* WorkStation = Cast<ABaseWorkStation>(SpawnActor());
	if (IsValid(WorkStation) == false) {
		UE_LOG(LogTemp, Error, TEXT("ABuilderItem::SetIsActive IsValid(WorkStation) == false"));
		return;
	}
	Village->AddWorkStationToColony(WorkStation);
	CurrentProjection->Destroy();
	CurrentProjection = nullptr;
}

void ABuilderItem::LoadFromDataTable()
{
	if (CurrentStationName == "")
	{
		Super::LoadFromDataTable();
		return;
	}

	if (IsValid(SecondaryDataTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ABuilderItemLoadFromDataTable() IsValid(DataTable) == false from %s"), *GetClass()->GetName());
		return;
	}

	FWorkStationData* BuilderData = SecondaryDataTable->FindRow<FWorkStationData>(CurrentStationName, "");

	if (BuilderData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ABuilderItem::LoadFromDataTable() BuilderData == nullptr from %s"), *GetClass()->GetName());
		return;
	}

	ActorToSpawn		 = BuilderData->ActorToSpawn;
	BuildProjectionClass = BuilderData->BuildProjectionClass;
}

void ABuilderItem::SpawnProjection()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ABuilderItem::SpawnProjection() IsValid(World) == false"));
		return ;
	}
	FVector Location = GetSpawnLocation();
	FRotator Rotation = GetSpawnRotation();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ABuildProjection* SpawnedProjection = World->SpawnActor<ABuildProjection>(BuildProjectionClass, Location, Rotation, Params);
	if (IsValid(SpawnedProjection) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ABuilderItem::SpawnProjection() IsValid(SpawnedActor) == false"));
		return;
	}
	CurrentProjection = SpawnedProjection;
}

FVector ABuilderItem::GetSpawnLocation()
{
	if (CurrentProjection == nullptr)
	{
		return FVector(0, 0, 0);
	}

	return CurrentProjection->GetActorLocation();
}

FRotator ABuilderItem::GetSpawnRotation()
{
	if (CurrentProjection == nullptr)
	{
		return FRotator(0, 0, 0);
	}
	return CurrentProjection->GetActorRotation();
}

void ABuilderItem::OnDrop()
{
	if (IsValid(CurrentProjection) == true)
	{
		CurrentProjection->Destroy();
		CurrentProjection = nullptr;
	}
}
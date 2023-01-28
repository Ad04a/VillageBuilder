// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Items/Tools/Tool.h"

ATool::ATool()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATool::BeginPlay()
{
	Super::BeginPlay();
	LoadFromDataTable();
}

void ATool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsActive) {
		return;
	}
	FVector StartTrace = MeshComponent->GetSocketLocation("start");
	FVector EndTrace = MeshComponent->GetSocketLocation("end");
	FVector HandleStartTrace = MeshComponent->GetSocketLocation("handle_start");
	FVector HandleEndTrace = MeshComponent->GetSocketLocation("handle_end");

	const FName TraceTag("MyTraceTag2");

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ATool::Tick IsValid(World) == false"));
		return;
	}
	//World->DebugDrawTraceTag = TraceTag;

	FHitResult HitResult = FHitResult();
	FHitResult HandleHitResult = FHitResult();
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);
	CQP.AddIgnoredActor(Cast<AActor>(Cast<ACharacter>(UsingVillager)));
	for (AActor* Damaged : DamagedActors) {
		CQP.AddIgnoredActor(Damaged);
	}
	CQP.TraceTag = TraceTag;
	World->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_WorldDynamic, CQP);
	World->LineTraceSingleByChannel(HandleHitResult, HandleStartTrace, HandleEndTrace, ECC_WorldDynamic, CQP);
	AActor* HitActor = HitResult.GetActor();
	AActor* HandleHitActor = HandleHitResult.GetActor();
	if (HitActor == nullptr && HandleHitActor == nullptr)
	{
		return;
	}

	float Damage = BaseDamage;
	if (HitActor != nullptr )
	{
		HitActor->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
		DamagedActors.Add(HitActor);
	}
	if (HandleHitActor != nullptr)
	{
		HandleHitActor->TakeDamage(Damage/3, FDamageEvent(), GetInstigatorController(), this);
		DamagedActors.Add(HandleHitActor);
	}
}

void ATool::Use(class AVillager* User, EItemActionType ActionType)
{
	Super::Use(User, ActionType);
	DamagedActors.Empty();
}

void ATool::LoadFromDataTable()
{
	Super::LoadFromDataTable();
	
	if (IsValid(SecondaryDataTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ATool::LoadFromDataTable() IsValid(DataTable) == false from %s"), *GetClass()->GetName());
		return;
	}

	FToolData* ToolData = SecondaryDataTable->FindRow<FToolData>(GetClass()->GetFName(), "");

	if (ToolData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ATool::LoadFromDataTable() ToolData == nullptr from %s"), *GetClass()->GetName());
		return;
	}

	BaseDamage = ToolData->BaseDamage;
}
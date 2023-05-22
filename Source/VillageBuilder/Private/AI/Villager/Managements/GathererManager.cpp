// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Managements/GathererManager.h"
#include "Characters/Villager.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

bool UGathererManager::CheckGivenKeys()
{
	if (GivenKeys.Num() != 1)
	{
		UE_LOG(LogTemp, Error, TEXT("UBuilderManager::CheckGivenKeys Number of needed keys is 1 but %d were given"), GivenKeys.Num());
		return false;
	}
	if (GivenKeys[0].SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		UE_LOG(LogTemp, Error, TEXT("UBuilderManager::CheckGivenKeys First key is not of type Object"));
		return false;
	}
	return true;
}

void UGathererManager::Init(class AVillager* InGatherer, float BaseRadius, TSubclassOf<class AItem> SearchClass)
{
	Gatherer = InGatherer;
	Radius = BaseRadius;
	TargetClass = SearchClass;
}

void UGathererManager::Tick(float DeltaTime)
{
	if (CanTick == false)
	{
		return;
	}

	Super::Tick(DeltaTime);

	if (IsValid(Gatherer) == false)
	{
		UE_LOG(LogTemp, Error, TEXT(" UGathererManager::Tick IsValid(Gatherer) == false"));
		return;
	}

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT(" UGathererManager::Tick IsValid(World) == false"));
		return;
	}
	TArray<FHitResult> OutHits;

	FCollisionQueryParams CQP;
	CQP.ClearIgnoredActors();
	for (AActor* Actor : RememberedItems)
	{
		CQP.AddIgnoredActor(Actor);
	}

	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	World->SweepMultiByChannel(OutHits, Gatherer->GetActorLocation(), Gatherer->GetActorLocation(), FQuat::MakeFromRotator(Gatherer->GetActorRotation()),
		ECC_GameTraceChannel2, Shape, CQP, FCollisionResponseParams::FCollisionResponseParams());

	for (FHitResult Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor->IsA(TargetClass) == false)
		{
			continue;
		}
		RememberedItems.Add(HitActor);
	}
	for (int i = RememberedItems.Num() - 1; i >= 0; i--)
	{
		if (IsValid(RememberedItems[i]) == false)
		{
			RememberedItems.RemoveAt(i);
		}
	}
	if (RememberedItems.IsEmpty() == true)
	{
		BlackBoard->ClearValue(GivenKeys[0].SelectedKeyName);
		return;
	}
	BlackBoard->SetValueAsObject(GivenKeys[0].SelectedKeyName, RememberedItems[0]);

}

void UGathererManager::Clear(AVillager* InVillager)
{
	Init(nullptr, 0, nullptr);
	Super::Clear(InVillager);
}
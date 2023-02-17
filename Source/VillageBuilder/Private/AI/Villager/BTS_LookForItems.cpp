// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/BTS_LookForItems.h"
#include "Kismet/KismetSystemLibrary.h"

UBTS_LookForItems::UBTS_LookForItems()
{
	NodeName = "LookForItems";
	bNotifyTick = true;
	bNotifyBecomeRelevant = true;
}

void UBTS_LookForItems::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_LookForItems::OnBecomeRelevant IsValid(World) == false"));
		return;
	}

	Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_LookForItems::OnBecomeRelevant IsValid(Controller) == false"));
		return;
	}
	BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_LookForItems::OnBecomeRelevant IsValid(BlackBoard) == false"));
		return;
	}
	Villager = Controller->GetControlledVillager();
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_LookForItems::OnBecomeRelevant IsValid(Villager) == false"));
		return;
	}
}

void UBTS_LookForItems::TickNode(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory, float DeltaSeconds)
{
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_LookForItems::TickNode IsValid(Villager) == false"));
		return;
	}
	AActor* FirstRemembered = Cast<AActor>(BlackBoard->GetValueAsObject(WriteInto.SelectedKeyName));
	if (IsValid(FirstRemembered) == true)
	{
		return;
	}
	Super::TickNode(OwnerComponent, NodeMemory, DeltaSeconds);
	
	TArray<FHitResult> OutHits;

	FCollisionQueryParams CQP;
	CQP.ClearIgnoredActors();
	for ( AActor* Actor : Controller->GetRememberdActors())
	{
		CQP.AddIgnoredActor(Actor);
	}

	FCollisionShape Shape;
	Shape.SetSphere(SearchRadius);
	
	World->SweepMultiByChannel(OutHits, Villager->GetActorLocation(), Villager->GetActorLocation(), FQuat::MakeFromRotator(Villager->GetActorRotation()), 
								ECC_GameTraceChannel2, Shape, CQP, FCollisionResponseParams::FCollisionResponseParams());
	
	for (FHitResult Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor->IsA(SearchClass) == false)
		{
			continue;
		}
		Controller->AddRememberdActor(HitActor);
	}

	FirstRemembered = Controller->GetFirstRememebred();
	if (IsValid(FirstRemembered) == false)
	{
		BlackBoard->ClearValue(WriteInto.SelectedKeyName);
		return;
	}
	
	BlackBoard->SetValueAsObject(WriteInto.SelectedKeyName, FirstRemembered);
}
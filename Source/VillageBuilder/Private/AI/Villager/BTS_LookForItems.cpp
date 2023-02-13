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

	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
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
	Super::TickNode(OwnerComponent, NodeMemory, DeltaSeconds);
	
	TArray<FHitResult> OutHits;

	FCollisionQueryParams CQP;
	const FName TraceTag("MyTraceTag3");
	//World->DebugDrawTraceTag = TraceTag;
	CQP.TraceTag = TraceTag;
	CQP.ClearIgnoredActors();
	for (AActor* Actor : RememberedActors)
	{
		CQP.AddIgnoredActor(Actor);
	}

	FCollisionShape Shape;
	Shape.SetSphere(SearchRadius);
	
	World->SweepMultiByChannel(OutHits, Villager->GetActorLocation(), Villager->GetActorLocation(), FQuat::MakeFromRotator(Villager->GetActorRotation()), 
								ECC_GameTraceChannel2, Shape, CQP, FCollisionResponseParams::FCollisionResponseParams());
	UE_LOG(LogTemp, Error, TEXT("NAPRAIH"));
	for (FHitResult Hit : OutHits)
	{
		UE_LOG(LogTemp, Error, TEXT("PROBVAME"));
		AActor* HitActor = Hit.GetActor();
		if (HitActor->IsA(SearchClass) == false)
		{
			continue;
		}
		UE_LOG(LogTemp, Warning, TEXT("IMAME"));
		RememberedActors.Add(HitActor);
	}
	if (RememberedActors.IsEmpty() == true)
	{
		UE_LOG(LogTemp, Error, TEXT("NEMAME"));
		return;
	}

	AActor* Remembered = Cast<AActor>(BlackBoard->GetValueAsObject(WriteInto.SelectedKeyName));
	if (IsValid(Remembered) == true)
	{
		UE_LOG(LogTemp, Error, TEXT("POMNIM VECHE"));
		return;
	}
	//TArray<AActor*> OutActors = RememberedActors.Array();
	
	BlackBoard->SetValueAsObject(WriteInto.SelectedKeyName, RememberedActors[0]);
	RememberedActors.Remove(0);
}
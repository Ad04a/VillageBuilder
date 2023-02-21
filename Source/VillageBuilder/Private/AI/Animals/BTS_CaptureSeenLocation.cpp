// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Animals/BTS_CaptureSeenLocation.h"
#include "Kismet/KismetSystemLibrary.h"

UBTS_CaptureSeenLocation::UBTS_CaptureSeenLocation()
{
	NodeName = "CaptureSeenLocation";
	bNotifyBecomeRelevant = true;
}

void UBTS_CaptureSeenLocation::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_CaptureSeenLocation::OnBecomeRelevant IsValid(World) == false"));
		return;
	}

	AAnimalAIController* Controller = Cast<AAnimalAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_CaptureSeenLocation::OnBecomeRelevant IsValid(Controller) == false"));
		return;
	}
	BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTS_CaptureSeenLocation::OnBecomeRelevant IsValid(BlackBoard) == false"));
		return;
	}
	Controller->OnVillagerSeen.BindDynamic(this, &UBTS_CaptureSeenLocation::WriteCapturedLocation);
}

void UBTS_CaptureSeenLocation::WriteCapturedLocation(FVector Location)
{
	BlackBoard->SetValueAsVector(WriteInto.SelectedKeyName, Location);
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AI/Animals/AnimalAIController.h"

#include "BTS_CaptureSeenLocation.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTS_CaptureSeenLocation : public UBTService
{
	GENERATED_BODY()
public:
	UBTS_CaptureSeenLocation();
private:
	UBlackboardComponent* BlackBoard;

	UFUNCTION()
	void WriteCapturedLocation(FVector Location);
protected:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector WriteInto;

	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)override;
};

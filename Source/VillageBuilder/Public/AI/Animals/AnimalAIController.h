// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/GeneralAIController.h"
#include "AnimalAIController.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FVillagerSeenSignature, FVector, Location);

UCLASS()
class VILLAGEBUILDER_API AAnimalAIController : public AGeneralAIController
{
	GENERATED_BODY()
protected:

	virtual void ActorDetected(AActor* Actor, struct FAIStimulus const Stimulus) override;
public:
	FVillagerSeenSignature OnVillagerSeen;
};

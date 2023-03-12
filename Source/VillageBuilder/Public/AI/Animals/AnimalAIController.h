// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/GeneralAIController.h"
#include "Engine/DataTable.h"
#include "AnimalAIController.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FVillagerSeenSignature, FVector, Location);

USTRUCT(BlueprintType)
struct FAnimalBehaviorData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBehaviorTree* BehaviorTree;

};

UCLASS()
class VILLAGEBUILDER_API AAnimalAIController : public AGeneralAIController
{
	GENERATED_BODY()
protected:
	void OnPossess(APawn* const InPawn) override;
	virtual void ActorDetected(AActor* Actor, struct FAIStimulus const Stimulus) override;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDataTable* BehaviorDataTable = nullptr;

	FVillagerSeenSignature OnVillagerSeen;
};

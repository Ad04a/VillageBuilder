// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/GeneralAIController.h"
#include "Characters/Villager.h" 
#include "Headers/AIStates.h"
#include "VillagerAIController.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API AVillagerAIController : public AGeneralAIController
{
	GENERATED_BODY()
	
public:

private:

	UPROPERTY(VisibleAnywhere, Category = Blackboard)
	TArray<AActor*> RememberedActors;

	class AVillager* ControlledVillager;

	UFUNCTION()
	void RegisterAIState(APawn* ControlledPawn, EAIState State);

public:
	UPROPERTY(VisibleAnywhere, Category = Blackboard)
	class UWorkerManager* WorkManager;

	void OnPossess(APawn* const InPawn) override;

	AVillager* GetControlledVillager()const;
	void AddRememberdActor(AActor* InActor);
	AActor* GetFirstRememebred();
	TArray<AActor*> GetRememberdActors() const{ return RememberedActors; }
};

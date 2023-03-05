// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/GeneralAIController.h"
#include "Characters/Villager.h" 
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

public:
	UPROPERTY(VisibleAnywhere, Category = Blackboard)
	class UWorkerManager* WorkManager;

	AVillager* GetControlledVillager()const;
	void AddRememberdActor(AActor* InActor);
	AActor* GetFirstRememebred();
	TArray<AActor*> GetRememberdActors() const{ return RememberedActors; }
};

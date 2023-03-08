// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_InitGathererManager.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTT_InitGathererManager : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = Gartherer)
	float BaseRadius;

	UPROPERTY(EditAnywhere, Category = Gartherer)
	TSubclassOf<class AItem> SearchClass;
public:
	UBTT_InitGathererManager();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

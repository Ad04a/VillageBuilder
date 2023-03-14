// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_SortInventory.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTT_SortInventory : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	TSubclassOf<class AItem> DesiredClass;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	bool UseFirstOfNeeded = false;

public:
	UBTT_SortInventory();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

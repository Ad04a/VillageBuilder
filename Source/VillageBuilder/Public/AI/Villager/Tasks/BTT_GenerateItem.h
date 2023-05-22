// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_GenerateItem.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTT_GenerateItem : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector WorkStation;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	TSubclassOf<class AItem> ItemToGenerate;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	int Quntity = 1;

public:
	UBTT_GenerateItem();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

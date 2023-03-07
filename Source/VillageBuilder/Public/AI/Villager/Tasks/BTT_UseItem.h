// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Headers/ItemActionEnums.h"
#include "BTT_UseItem.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTT_UseItem : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	TEnumAsByte<EItemActionType> ActionType;

public:
	UBTT_UseItem();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

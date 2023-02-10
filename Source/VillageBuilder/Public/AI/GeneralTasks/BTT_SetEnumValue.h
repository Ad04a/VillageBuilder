// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Headers/ItemInfo.h"

#include "AI/Villager/VillagerAIController.h"

#include "BTT_SetEnumValue.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTT_SetEnumValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	TEnumAsByte<EItemType>  SetToValue;
public:
	UBTT_SetEnumValue();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
};

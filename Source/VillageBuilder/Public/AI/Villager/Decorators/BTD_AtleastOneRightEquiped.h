// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_AtleastOneRightEquiped.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UBTD_AtleastOneRightEquiped : public UBTDecorator
{
	GENERATED_BODY()
protected:

public:
	UBTD_AtleastOneRightEquiped();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) const override;
};

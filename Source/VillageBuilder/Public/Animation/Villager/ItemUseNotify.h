// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Headers/ItemActionEnums.h"
#include "ItemUseNotify.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UItemUseNotify : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EItemActionType> ActionType;

public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widgets/Gameplay/StatWidgetBase.h"
#include "UI/Widgets/Gameplay/InteractionWidgetBase.h"
#include "GameplayHUDBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractingBroadcastetSignature, FText, ActionText);

UCLASS()
class VILLAGEBUILDER_API AGameplayHUDBase : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UStatWidgetBase> StatWidgetClass;

	UPROPERTY()
	class UStatWidgetBase* StatWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInteractionWidgetBase> InteractionWidgetClass;

	UPROPERTY()
	class UInteractionWidgetBase* InteractionWidget;

	FInteractingBroadcastetSignature OnInteraction;

	virtual void BeginPlay()override;

	void Clear();

public:
	UFUNCTION()
	void ShowStats();

	UFUNCTION()
	void ShowInteraction(FText Action);

	UFUNCTION()
	void BindPlayerToStatWidget(AVillager* Player);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widgets/Gameplay/StatWidgetBase.h"
#include "UI/Widgets/Gameplay/InteractionWidgetBase.h"
#include "UI/Widgets/Gameplay/TraitMenuWidgetBase.h"
#include "Headers/StatAndTraitEnums.h"
#include "GameplayHUDBase.generated.h"


UCLASS()
class VILLAGEBUILDER_API AGameplayHUDBase : public AHUD
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void BindVillagerToTraitMenuWidget(AVillager* Villager);

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UStatWidgetBase> StatWidgetClass;

	UPROPERTY()
	class UStatWidgetBase* StatWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInteractionWidgetBase> InteractionWidgetClass;

	UPROPERTY()
	class UInteractionWidgetBase* InteractionWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTraitMenuWidgetBase> TraitMenuWidgetClass;

	UPROPERTY()
	class UTraitMenuWidgetBase* TraitMenuWidget;

	virtual void BeginPlay()override;

	void Clear();

public:
	UFUNCTION()
	void ShowStats();

	UFUNCTION()
	void ShowInteraction(FText Action);

	UFUNCTION()
	void BindPlayerToStatWidget(AVillager* Player);

	UFUNCTION()
	void ShowTraitMenu(AVillager* Caller);
};

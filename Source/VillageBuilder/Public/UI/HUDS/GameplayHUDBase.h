// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widgets/Gameplay/StatWidgetBase.h"
#include "UI/Widgets/Gameplay/InteractionWidgetBase.h"
#include "UI/Widgets/Gameplay/TraitMenuWidgetBase.h"
#include "UI/Widgets/Gameplay/EmployeeMenuWidgetBase.h"
#include "UI/Widgets/Gameplay/InGameOptionsWidgetBase.h"
#include "UI/Widgets/Gameplay/BuildMenuWidgetBase.h"
#include "UI/Widgets/Gameplay/InventoryWidgetBase.h"
#include "Headers/StatAndTraitEnums.h"
#include "GameplayHUDBase.generated.h"


UCLASS()
class VILLAGEBUILDER_API AGameplayHUDBase : public AHUD
{
	GENERATED_BODY()

private:
	class AGameplayModeBase* GameMode;
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

	UPROPERTY(EditAnywhere)
	TSubclassOf<UEmployeeMenuWidgetBase> EmployeeMenuWidgetClass;

	UPROPERTY()
	class UEmployeeMenuWidgetBase* EmployeeMenuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInGameOptionsWidgetBase> InGameOptionsWidgetClass;

	UPROPERTY()
	class UInGameOptionsWidgetBase* UInGameOptionsWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBuildMenuWidgetBase> BuildMenuWidgetBaseClass;

	UPROPERTY()
	class UBuildMenuWidgetBase* BuildMenuWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidgetBase> InventoryWidgetBaseClass;

	
	virtual void BeginPlay()override;

	void Clear();

public:
	UFUNCTION()
	void ShowStats(AVillager* Villager);

	UFUNCTION()
	void ShowInteraction(FText Action);

	UFUNCTION()
	void ShowTraitMenu(AVillager* Caller);

	UFUNCTION()
	void ShowEmployeeMenu(ABaseWorkStation* WorkStation);

	UFUNCTION()
	void ToggleOptions();

	UFUNCTION()
	void ShowBuildMenu();
};

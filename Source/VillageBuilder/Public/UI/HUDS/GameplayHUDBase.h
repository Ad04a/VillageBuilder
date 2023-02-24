// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
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
	TSubclassOf<class UStatWidgetBase> StatWidgetClass;

	UPROPERTY()
	class UStatWidgetBase* StatWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInteractionWidgetBase> InteractionWidgetClass;

	UPROPERTY()
	class UInteractionWidgetBase* InteractionWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UTraitMenuWidgetBase> TraitMenuWidgetClass;

	UPROPERTY()
	class UTraitMenuWidgetBase* TraitMenuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UEmployeeMenuWidgetBase> EmployeeMenuWidgetClass;

	UPROPERTY()
	class UEmployeeMenuWidgetBase* EmployeeMenuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInGameOptionsWidgetBase> InGameOptionsWidgetClass;

	UPROPERTY()
	class UInGameOptionsWidgetBase* UInGameOptionsWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBuildMenuWidgetBase> BuildMenuWidgetBaseClass;

	UPROPERTY()
	class UBuildMenuWidgetBase* BuildMenuWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventoryWidgetBase> InventoryWidgetBaseClass;

	
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

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widgets/Gameplay/StatWidgetBase.h"
#include "GameplayHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API AGameplayHUDBase : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UStatWidgetBase> StatWidgetClass;

	UPROPERTY()
	class UStatWidgetBase* StatWidget;

	virtual void BeginPlay()override;

	void Clear();

public:
	UFUNCTION()
	void ShowStats();

	UFUNCTION()
	void BindPlayerToStatWidget(AVillager* Player);
};

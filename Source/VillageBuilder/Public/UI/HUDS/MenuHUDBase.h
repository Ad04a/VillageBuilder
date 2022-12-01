// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widgets/Menu/StartingWidgetBase.h"
#include "MenuHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API AMenuHUDBase : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UStartingWidgetBase> MainMenuWidgetClass;

	UPROPERTY()
	class UStartingWidgetBase* MainMenuWidget;

	void Clear();

	virtual void BeginPlay()override;

public:

	UFUNCTION()
	void ShowMenu();

};

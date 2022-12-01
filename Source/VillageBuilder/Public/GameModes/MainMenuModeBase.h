// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API AMainMenuModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();
};

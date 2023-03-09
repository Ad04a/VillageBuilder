// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuModeBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FSaveSlotsFoundSignature, TArray<FString>, SaveSlots);

UCLASS()
class VILLAGEBUILDER_API AMainMenuModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	FName Gameplay = "NewWorld";

public:

	FSaveSlotsFoundSignature OnSaveSlotsFound;

	UFUNCTION()
	void StartGame(FString SlotName);

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void GetAllSlots();

	UFUNCTION()
	void AddSave(FString SaveName);
};

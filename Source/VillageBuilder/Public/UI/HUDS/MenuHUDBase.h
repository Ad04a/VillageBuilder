// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widgets/Menu/StartingWidgetBase.h"
#include "UI/Widgets/Menu/ChooseSaveGameWidgetBase.h"
#include "UI/Widgets/Menu/NewSaveWidgetBase.h"
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

	UPROPERTY(EditAnywhere)
	TSubclassOf<UChooseSaveGameWidgetBase> ChooseSaveGameWidgetClass;

	UPROPERTY()
	class UChooseSaveGameWidgetBase* ChooseSaveGameWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UNewSaveWidgetBase> NewSaveWidgetClass;

	UPROPERTY()
	class UNewSaveWidgetBase* NewSaveWidget;

	void Clear();

	virtual void BeginPlay()override;

public:

	UFUNCTION()
	void ShowMenu();

	UFUNCTION()
	void ShowChooseSaveGame(TArray<FString> SaveSlots);

	UFUNCTION()
	void ShowNewSave();

	UFUNCTION()
	void RemoveNewSave();

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "StartingWidgetBase.generated.h"

/**
 * 
 */

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonClicked);

UCLASS()
class VILLAGEBUILDER_API UStartingWidgetBase : public UUserWidget
{
	GENERATED_BODY()
private:

	UFUNCTION()
	void OnPlayClicked();

	UFUNCTION()
	void OnQuitClicked();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Play;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Quit;


	virtual void NativeConstruct() override;

public:
	FButtonClicked PlayClicked;
	FButtonClicked QuitClicked;
};

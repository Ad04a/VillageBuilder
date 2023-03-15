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
	class UDataLink* CurrentDataLink = nullptr;
protected:

	UPROPERTY()
	class UMainPurposeWidgetBase* MainWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainPurposeWidgetBase> MainWidgetClass;

	UPROPERTY()
	class UDataLinkWidgetBase* DataLinkWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDataLinkWidgetBase> DataLinkWidgetBaseClass;
	
	
	virtual void BeginPlay()override;

public:

	UFUNCTION()
	void VisualizeDataLink(class UDataLink* InDataLink);

	UFUNCTION()
	void ShowMainWidget(class AVillageMayor* Player);

	UFUNCTION()
	void Clear();
};

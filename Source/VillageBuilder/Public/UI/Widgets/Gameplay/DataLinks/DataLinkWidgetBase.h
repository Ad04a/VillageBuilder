// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/VisualizationTypes.h"
#include "DataLinkWidgetBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLinkClosedSignature);

UCLASS()
class VILLAGEBUILDER_API UDataLinkWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UVisualModuleWidgetBase> VisualModuleWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UWrapBox* ModuleWrapBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* CloseButton;;

	UFUNCTION()
	void ButtonClicked();

public:
	void Init(TMap<TEnumAsByte<EVisualiationTypes>, class UVisualizationInfo*> InitiatorVisualizationInfos, TMap<TEnumAsByte<EVisualiationTypes>, class UVisualizationInfo*> TargetVisualizationInfos);
	void NativeOnInitialized() override;
	FLinkClosedSignature OnLinkClosed;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Gameplay/DataLinks/VisualFragmentWidgetBase.h"

#include "Headers/RequestVisual.h"

#include "RequestMenuWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE(FUpdateNeededSignature);

UCLASS()
class VILLAGEBUILDER_API URequestMenuWidgetBase : public UVisualFragmentWidgetBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UScrollBox* VillagerScrollBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class URequestWidgetBase> RequestWidgetClass;

	UFUNCTION()
	void GetUpdatedRequests(TArray<FVisualRequest> Requests);

public:
	FUpdateNeededSignature OnUpdateNeeded;
	virtual void Init(class UVisualizationInfo* VisualInfo) override;
	virtual void NativeConstruct() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "UI/Widgets/Gameplay/DataLinks/VisualFragmentWidgetBase.h"
#include "BuildMenuWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam( FBuildingSelectedSignature, FString, BuildingName);

UCLASS()
class VILLAGEBUILDER_API UBuildMenuWidgetBase : public UVisualFragmentWidgetBase
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UScrollBox* BuildingScrollBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UBuildingSelectWidgetBase> BuildingSelectClass;

	UFUNCTION()
	void BuildingSelected(FString SelectedBuildingName);

public:
	virtual void Init(class UVisualizationInfo* VisualInfo) override;

	FBuildingSelectedSignature OnBuildingSelected;
};

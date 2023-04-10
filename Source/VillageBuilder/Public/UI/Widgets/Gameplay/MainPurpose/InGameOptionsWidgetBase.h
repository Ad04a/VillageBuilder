// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/Widgets/Gameplay/DataLinks/VisualFragmentWidgetBase.h"
#include "Headers/OptionStructures.h"
#include "InGameOptionsWidgetBase.generated.h"

DECLARE_DYNAMIC_DELEGATE(FButtunClickedSignature);

UENUM(BlueprintType)
enum ESectionType {
	Graphics    UMETA(DisplayName = "Graphics"),
	Sound       UMETA(DisplayName = "Sound"),
	Controls 	UMETA(DisplayName = "Controls")

};
ENUM_RANGE_BY_FIRST_AND_LAST(ESectionType, ESectionType::Graphics, ESectionType::Graphics);

UCLASS()
class VILLAGEBUILDER_API UInGameOptionsWidgetBase : public UVisualFragmentWidgetBase
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* ExitButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UWrapBox* GraphicsWrap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* GraphicsButton;

	UPROPERTY(EditDefaultsOnly)
	TMap<TEnumAsByte<ESectionType>, TSubclassOf<UUserWidget>> SectionTypes;

	UPROPERTY()
	TMap<TEnumAsByte<ESectionType>, UUserWidget*> Sections;

	TMap<class UWrapBox*, TEnumAsByte<ESectionType>> Types;

	TMap<class UButton*, class UWrapBox*> Relations;

	UFUNCTION()
	void ToggleGraphics();

	void Manage(class UButton* ButtonForSection);

	UFUNCTION()
	void UpdateGraphics(FGraphicsSettings InGraphicsSettings);

public:
	virtual void Init(class UVisualizationInfo* VisualInfo) override;
	virtual void NativeOnInitialized() override;

};

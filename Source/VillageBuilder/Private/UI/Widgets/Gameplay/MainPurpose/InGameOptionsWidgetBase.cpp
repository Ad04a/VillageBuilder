// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/MainPurpose/InGameOptionsWidgetBase.h"
#include "UI/Widgets/Gameplay/MainPurpose/GraphicsQualityWidgetBase.h"
#include "DataTransfers/VisualizationInfos/OptionsVisualInfo.h"

#include "Components/Button.h"
#include "Components/WrapBox.h"

void UInGameOptionsWidgetBase::NativeOnInitialized()
{
	Relations.Add(GraphicsButton, GraphicsWrap);
	Types.Add(GraphicsWrap, ESectionType::Graphics);
	GraphicsButton->OnClicked.AddDynamic(this, &UInGameOptionsWidgetBase::ToggleGraphics);

}

void UInGameOptionsWidgetBase::Init(UVisualizationInfo* VisualInfo)
{
	UOptionsVisualInfo* OptionsInfo = Cast<UOptionsVisualInfo>(VisualInfo);
	if (IsValid(OptionsInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInGameOptionsWidgetBase::Init Given VisualInfo doesnt mach the required type"));
	}
	ExitButton->OnClicked.AddDynamic(OptionsInfo, &UOptionsVisualInfo::ExitGame);

	for (ESectionType SectionType : TEnumRange<ESectionType>())
	{
		TSubclassOf<UUserWidget> WidgetClass = *SectionTypes.Find(SectionType);
		if (IsValid(WidgetClass) == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("UInGameOptionsWidgetBase::Init No SectionType specified for current section"));
			continue;
		}
		UWorld* World = GetWorld();
		if (IsValid(World) == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("UInGameOptionsWidgetBase::Init IsValid(World) == false"));
			continue;
		}
		UUserWidget* Section = CreateWidget<UUserWidget>(World, WidgetClass);
		if (IsValid(Section) == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("UInGameOptionsWidgetBase::Init IsValid(Section) == false"));
			continue;
		}
		Sections.Add(SectionType, Section);

	};
	SectionTypes.Empty();

	UGraphicsQualityWidgetBase* GraphicsWidget = Cast<UGraphicsQualityWidgetBase>(*Sections.Find(ESectionType::Graphics));
	if (IsValid(GraphicsWidget) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInGameOptionsWidgetBase::Manage IsValid(GraphicsWidget) == false"));
		return;
	}
	GraphicsWidget->OnGraphicsUpdated.BindDynamic(OptionsInfo, &UOptionsVisualInfo::RecieveUpdatedGraphics);
	GraphicsWidget->OnQualityUpdated.BindDynamic(OptionsInfo, &UOptionsVisualInfo::RecieveUpdatedQuality);
	GraphicsWidget->RequestUpdate.BindDynamic(OptionsInfo, &UOptionsVisualInfo::RecieveUpdatedGraphics);
	OptionsInfo->OnGraphicsSaved.BindDynamic(GraphicsWidget, &UGraphicsQualityWidgetBase::UpdateScaleability);

}

void UInGameOptionsWidgetBase::UpdateGraphics(FGraphicsSettings InGraphicsSettings)
{

}

void UInGameOptionsWidgetBase::ToggleGraphics()
{
	Manage(GraphicsButton);
}


void UInGameOptionsWidgetBase::Manage( UButton* ButtonForSection)
{
	UWrapBox* Wrap = *Relations.Find(ButtonForSection);
	if (IsValid(Wrap) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInGameOptionsWidgetBase::Manage No WrapBox specified for current section"));
		return;
	}
	if (Wrap->GetChildrenCount() > 1)
	{
		for (int i = Wrap->GetChildrenCount() - 1; i > 0; i--)
		{
			Wrap->RemoveChildAt(i);
		}
		return;
	}
	ESectionType SectionType = *Types.Find(Wrap);
	
	UUserWidget* Section = *Sections.Find(SectionType);

	Wrap->AddChild(Section);
}
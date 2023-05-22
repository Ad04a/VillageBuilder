// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Gameplay/MainPurpose/RequestWidgetBase.h"
#include "UI/Widgets/Gameplay/MainPurpose/RequestModuleWidgetBase.h"

#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void URequestWidgetBase::Init(FText Villager, TMap<FString, int> Clasess, bool IsFull)
{
	VillagerName->SetText(Villager);

	int Offset = 0;

	UWorld* World = GetWorld();

	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT(" URequestWidgetBase::Init IsValid(World) == false"));
		return;
	}

	for (TPair<FString, int> Request : Clasess)
	{
		URequestModuleWidgetBase* Module = CreateWidget<URequestModuleWidgetBase>(World, RequestModuleClass);
		if (IsValid(Module) == false)
		{
			UE_LOG(LogTemp, Error, TEXT(" URequestWidgetBase::Init IsValid(Module) == false"));
			return;
		}
		Module->Init(Request.Key, Request.Value);

		UCanvasPanelSlot* WidgetSlot = Cast<UCanvasPanelSlot>(RequestCanvas->AddChild(Module));

		WidgetSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
		WidgetSlot->SetOffsets(FMargin(0.f, Offset, 0.f, -Offset));
		WidgetSlot->SetAutoSize(true);
		Offset += ItemOffset;
	}

	if (IsFull == false)
	{
		return;
	}

	URequestModuleWidgetBase* Module = CreateWidget<URequestModuleWidgetBase>(World, RequestModuleClass);
	if (IsValid(Module) == false)
	{
		UE_LOG(LogTemp, Error, TEXT(" URequestWidgetBase::Init IsValid(Module) == false"));
		return;
	}
	Module->Init("Don't have enough inventory space", 0);

	UCanvasPanelSlot* WidgetSlot = Cast<UCanvasPanelSlot>(RequestCanvas->AddChild(Module));

	WidgetSlot->SetAnchors(FAnchors(1.f, 1.f, 1.f, 1.f));
	WidgetSlot->SetOffsets(FMargin(0.f, Offset, 0.f, -Offset));
	WidgetSlot->SetAutoSize(true);

}
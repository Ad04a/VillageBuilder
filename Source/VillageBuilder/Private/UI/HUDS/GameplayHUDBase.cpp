// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUDS/GameplayHUDBase.h"
#include "GameModes/GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "UI/Widgets/Gameplay/InteractionWidgetBase.h"
#include "UI/Widgets/Gameplay/InGameOptionsWidgetBase.h"
#include "UI/Widgets/Gameplay/StatsAndTraits/StatWidgetBase.h"
#include "UI/Widgets/Gameplay/StatsAndTraits/TraitMenuWidgetBase.h"
#include "UI/Widgets/Gameplay/Employment/EmployeeMenuWidgetBase.h"
#include "UI/Widgets/Gameplay/Building/BuildMenuWidgetBase.h"
#include "UI/Widgets/Gameplay/Inventory/InventoryWidgetBase.h"
#include "UI/Widgets/Gameplay/DataLinks/DataLinkWidgetBase.h"
#include "DataTransfers/DataLink.h"

void AGameplayHUDBase::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::BeginPlay() IsValid(World) == false"));
		return;
	}

	GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::BeginPlay() IsValid(GameMode) == false"));
		return;
	}

	GameMode->OnLinkNeedsVisualization.AddDynamic(this, &AGameplayHUDBase::VisualizeDataLink);

	InteractionWidget = Cast<UInteractionWidgetBase>(CreateWidget<UUserWidget>(World, InteractionWidgetClass));
	if (IsValid(InteractionWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::BeginPlay() IsValid(InteractionWidget) == false"));
		return;
	}

	UInGameOptionsWidget = Cast<UInGameOptionsWidgetBase>(CreateWidget<UUserWidget>(World, InGameOptionsWidgetClass));
	if (IsValid(UInGameOptionsWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::BeginPlay() IsValid(UInGameOptionsWidget) == false"));
		return;
	}
	UInGameOptionsWidget->OnExitClicked.BindDynamic(GameMode, &AGameplayModeBase::EndGame);
	UInGameOptionsWidget->OnContinueClicked.BindDynamic(this, &AGameplayHUDBase::ToggleOptions);

	DataLinkWidget = Cast<UDataLinkWidgetBase>(CreateWidget<UUserWidget>(World, DataLinkWidgetBaseClass));
	if (IsValid(DataLinkWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::BeginPlay() IsValid(DataLinkWidget) == false"));
		return;
	}

	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
}

void AGameplayHUDBase::VisualizeDataLink(UDataLink* InDataLink)
{
	if ((IsValid(PlayerOwner)  && IsValid(DataLinkWidget)) == false && IsValid(GameMode) == false)
	{
		return;
	}
	if (DataLinkWidget->IsInViewport() == true)
	{
		DataLinkWidget->RemoveFromViewport();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
		return;
	}
	DataLinkWidget->Init(InDataLink->GetInitiatorInfo(), InDataLink->GetTargetInfo());
	DataLinkWidget->OnLinkClosed.AddDynamic(InDataLink, &UDataLink::BreakConnection);
	InDataLink->OnLinkBroken.AddDynamic(this, &AGameplayHUDBase::VisualizeDataLink);
	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeUIOnly());
	DataLinkWidget->AddToViewport();
}

void AGameplayHUDBase::ShowInteraction(FText ActionText)
{
	if ((IsValid(PlayerOwner) && IsValid(InteractionWidget)) == false && IsValid(GameMode) == false) {
		return;
	}
	
	if (FText().EqualTo(ActionText)) {
		InteractionWidget->RemoveFromViewport();
		return;
	}
	
	InteractionWidget->UpdateInteractionText(ActionText);

	if (InteractionWidget->IsInViewport()==true) {
		return;
	}
	InteractionWidget->AddToViewport();
}

void AGameplayHUDBase::ToggleOptions()
{
	if ((IsValid(PlayerOwner) && IsValid(UInGameOptionsWidget)) == false && IsValid(GameMode) == false) {
		return;
	}
	if (UInGameOptionsWidget->IsInViewport() == true)
	{
		UInGameOptionsWidget->RemoveFromViewport();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
		return;
	}

	UInGameOptionsWidget->AddToViewport();
	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeUIOnly());
	
}

void AGameplayHUDBase::Clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

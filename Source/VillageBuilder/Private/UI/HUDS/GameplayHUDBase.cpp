// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUDS/GameplayHUDBase.h"
#include "GameModes/GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "UI/Widgets/Gameplay/MainPurpose/MainPurposeWidgetBase.h"
#include "UI/Widgets/Gameplay/DataLinks/DataLinkWidgetBase.h"
#include "DataTransfers/DataLink.h"
#include "Characters/VillageMayor.h"

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

	MainWidget = Cast<UMainPurposeWidgetBase>(CreateWidget<UUserWidget>(World, MainWidgetClass));
	if (IsValid(MainWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::BeginPlay() IsValid(MainWidget) == false"));
		return;
	}

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

void AGameplayHUDBase::ShowMainWidget(class AVillageMayor* Player)
{
	if ((IsValid(PlayerOwner) && IsValid(MainWidget)) == false && IsValid(GameMode) == false)
	{
		return;
	}
	Player->OnStatUpdated.AddDynamic(MainWidget, &UMainPurposeWidgetBase::PassStatUpdate);
	Player->OnInteraction.AddDynamic(MainWidget, &UMainPurposeWidgetBase::SetInteractionText);
	Player->OnDataLink.AddDynamic(MainWidget, &UMainPurposeWidgetBase::SetDataLinkText);
	Player->AcknowledgeWidgetBinding();
	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());

	MainWidget->AddToViewport();
}

void ShowInteraction(FText ActionText)
{
	/*if ((IsValid(PlayerOwner) && IsValid(InteractionWidget)) == false && IsValid(GameMode) == false) {
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
	InteractionWidget->AddToViewport();*/
}

void ToggleOptions()
{
	/*if ((IsValid(PlayerOwner) && IsValid(UInGameOptionsWidget)) == false && IsValid(GameMode) == false) {
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
	PlayerOwner->SetInputMode(FInputModeUIOnly());*/
	
}

void AGameplayHUDBase::Clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

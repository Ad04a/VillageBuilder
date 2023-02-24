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

	StatWidget = Cast<UStatWidgetBase>(CreateWidget<UUserWidget>(World, StatWidgetClass));
	if (IsValid(StatWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::BeginPlay() IsValid(StatWidget) == false"));
		return;
	}

	InteractionWidget = Cast<UInteractionWidgetBase>(CreateWidget<UUserWidget>(World, InteractionWidgetClass));
	if (IsValid(InteractionWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::BeginPlay() IsValid(InteractionWidget) == false"));
		return;
	}

	TraitMenuWidget = Cast<UTraitMenuWidgetBase>(CreateWidget<UUserWidget>(World, TraitMenuWidgetClass));
	if (IsValid(TraitMenuWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::BeginPlay() IsValid(TraitMenuWidget) == false"));
		return;
	}

	EmployeeMenuWidget = Cast<UEmployeeMenuWidgetBase>(CreateWidget<UUserWidget>(World, EmployeeMenuWidgetClass));
	if (IsValid(EmployeeMenuWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::BeginPlay() IsValid(EmployeeMenuWidget) == false"));
		return;
	}

	UInGameOptionsWidget = Cast<UInGameOptionsWidgetBase>(CreateWidget<UUserWidget>(World, InGameOptionsWidgetClass));
	if (IsValid(UInGameOptionsWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::BeginPlay() IsValid(UInGameOptionsWidget) == false"));
		return;
	}
	UInGameOptionsWidget->OnExitClicked.BindDynamic(GameMode, &AGameplayModeBase::EndGame);
	UInGameOptionsWidget->OnContinueClicked.BindDynamic(this, &AGameplayHUDBase::ToggleOptions);
	

	BuildMenuWidget = Cast<UBuildMenuWidgetBase>(CreateWidget<UUserWidget>(World, BuildMenuWidgetBaseClass));
	if (IsValid(BuildMenuWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::BeginPlay() IsValid(BuildMenuWidget) == false"));
		return;
	}
	BuildMenuWidget->OnCloseSignal.BindDynamic(this, &AGameplayHUDBase::ShowBuildMenu);
}

void AGameplayHUDBase::ShowStats(AVillager* Villager)
{
	if ((IsValid(PlayerOwner) && IsValid(StatWidget)) == false && IsValid(GameMode) == false) {
		return;
	}
	
	StatWidget->Init(Villager);
	StatWidget->AddToViewport();
	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
	
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

void AGameplayHUDBase::ShowTraitMenu(AVillager* Caller)
{
	
	if ((IsValid(PlayerOwner) && IsValid(TraitMenuWidget)) == false && IsValid(GameMode) == false) {
		return;
	}

	if (TraitMenuWidget->IsInViewport() == true) 
	{
		TraitMenuWidget->RemoveFromViewport();
		Caller->OnStatUpdated.RemoveAll(TraitMenuWidget);
		return;
	}

	TraitMenuWidget->Init(Caller);
	TraitMenuWidget->AddToViewport();
	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());

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

void AGameplayHUDBase::ShowEmployeeMenu(ABaseWorkStation* WorkStation)
{
	if ((IsValid(PlayerOwner) && IsValid(EmployeeMenuWidget)) == false && IsValid(GameMode) == false) {
		return;
	}

	AVillageManager* CurrentVillage = GameMode->GetCurrentVillage(WorkStation);
	if (IsValid(CurrentVillage) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::ShowEmployeeMenu() IsValid(CurrentVillage) == false"));
		return;
	}
	if (EmployeeMenuWidget->IsInViewport() == true) {
		CurrentVillage->OnVillagersUpdated.Unbind();
		EmployeeMenuWidget->OnVillagerEmployed.Unbind();
		EmployeeMenuWidget->RemoveFromViewport();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
		return;
	}
	EmployeeMenuWidget->Init();
	EmployeeMenuWidget->LoadVillagerWidgets();
	EmployeeMenuWidget->AddToViewport();
	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeGameAndUI());
	
}

void AGameplayHUDBase::ShowBuildMenu()
{
	if ((IsValid(PlayerOwner) && IsValid(BuildMenuWidget)) == false && IsValid(GameMode) == false) {
		return;
	}
	if (BuildMenuWidget->IsInViewport() == true) {
		BuildMenuWidget->RemoveFromViewport();
		BuildMenuWidget->OnBuildingSelected.Unbind();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
		return;
	}
	BuildMenuWidget->Init(GameMode->GetAllBuildingNames());
	BuildMenuWidget->OnBuildingSelected.BindDynamic(GameMode, &AGameplayModeBase::GivePlayerBuildItem);
	BuildMenuWidget->AddToViewport();
	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeUIOnly());
}

void AGameplayHUDBase::Clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

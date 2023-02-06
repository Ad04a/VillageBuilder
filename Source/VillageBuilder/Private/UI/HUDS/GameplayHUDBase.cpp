// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUDS/GameplayHUDBase.h"
#include "GameModes/GameplayModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"


void AGameplayHUDBase::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::BeginPlay() IsValid(World) == false"));
		return;
	}

	AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
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
}

void AGameplayHUDBase::ShowStats(AVillager* Villager)
{
	if ((IsValid(PlayerOwner) && IsValid(StatWidget)) == false) {
		return;
	}
	
	StatWidget->Init(Villager);
	StatWidget->AddToViewport();
	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
	
}

void AGameplayHUDBase::ShowInteraction(FText ActionText)
{
	if ((IsValid(PlayerOwner) && IsValid(InteractionWidget)) == false) {
		return;
	}
	
	if (FText().EqualTo(ActionText)) {
		InteractionWidget->RemoveFromViewport();
		return;
	}
	
	InteractionWidget->UpdateInteractionText(ActionText);

	if (InteractionWidget->GetIsVisible()==false) {
		InteractionWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
	}
}

void AGameplayHUDBase::ShowTraitMenu(AVillager* Caller)
{
	
	if ((IsValid(PlayerOwner) && IsValid(TraitMenuWidget)) == false) {
		return;
	}

	if (TraitMenuWidget->GetIsVisible()) 
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

void AGameplayHUDBase::ShowEmployeeMenu(ABaseWorkStation* WorkStation)
{
	if ((IsValid(PlayerOwner) && IsValid(EmployeeMenuWidget)) == false) {
		return;
	}
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::ShowEmployeeMenu() IsValid(World) == false"));
		return;
	}

	AGameplayModeBase* GameMode = Cast<AGameplayModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::ShowEmployeeMenu() IsValid(GameMode) == false"));
		return;
	}
	AVillageManager* CurrentVillage = GameMode->GetCurrentVillage(WorkStation);
	if (IsValid(CurrentVillage) == false) {
		UE_LOG(LogTemp, Error, TEXT("AGameplayHUDBase::ShowEmployeeMenu() IsValid(CurrentVillage) == false"));
		return;
	}
	if (EmployeeMenuWidget->GetIsVisible() == true) {
		CurrentVillage->OnVillagersUpdated.Unbind();
		EmployeeMenuWidget->OnVillagerEmployed.Unbind();
		EmployeeMenuWidget->RemoveFromViewport();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
		return;
	}
	EmployeeMenuWidget->Init(WorkStation);
	EmployeeMenuWidget->OnVillagerEmployed.BindDynamic(CurrentVillage, &AVillageManager::ManageEmployment);
	CurrentVillage->OnVillagersUpdated.BindDynamic(EmployeeMenuWidget, &UEmployeeMenuWidgetBase::LoadVillagerWidgets);
	EmployeeMenuWidget->LoadVillagerWidgets(CurrentVillage->GetAllVillagers());
	EmployeeMenuWidget->AddToViewport();
	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeGameAndUI());
	
}

void AGameplayHUDBase::Clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

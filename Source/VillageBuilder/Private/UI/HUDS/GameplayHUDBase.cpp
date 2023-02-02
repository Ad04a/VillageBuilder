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

	ShowStats();
}

void AGameplayHUDBase::ShowStats()
{
	if ((IsValid(PlayerOwner) && IsValid(StatWidget)) == false) {
		return;
	}
	
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

void AGameplayHUDBase::BindPlayerToStatWidget(AVillager* Player)
{
	Player->OnStatUpdated.AddDynamic(StatWidget, &UStatWidgetBase::SetStat);

	Player->AcknowledgeWidgetBinding();
}

void AGameplayHUDBase::BindVillagerToTraitMenuWidget(AVillager* Villager)
{

	Villager->OnStatUpdated.AddDynamic(TraitMenuWidget, &UTraitMenuWidgetBase::SetStat);
	Villager->AcknowledgeWidgetBinding();

	for (ETrait Trait : TEnumRange<ETrait>()) 
	{
		TraitMenuWidget->SetTrait(Trait, Villager->GetTrait(Trait));
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

	BindVillagerToTraitMenuWidget(Caller);
	TraitMenuWidget->AddToViewport();
	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());

}

void AGameplayHUDBase::ShowEmployeeMenu()
{
	if ((IsValid(PlayerOwner) && IsValid(EmployeeMenuWidget)) == false) {
		return;
	}
	if (EmployeeMenuWidget->GetIsVisible() == true) {
		EmployeeMenuWidget->RemoveFromViewport();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
		return;
	}

	EmployeeMenuWidget->AddToViewport();
	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeGameAndUI());
	
}

void AGameplayHUDBase::Clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

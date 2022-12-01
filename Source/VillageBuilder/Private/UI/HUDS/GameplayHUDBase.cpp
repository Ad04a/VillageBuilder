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

	ShowStats();
}

void AGameplayHUDBase::ShowStats()
{
	Clear();

	if (PlayerOwner && StatWidget) {
		StatWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
	}
}

void AGameplayHUDBase::BindPlayerToStatWidget(AVillager* Player)
{
	Player->OnHungerUpdated.AddDynamic(StatWidget, &UStatWidgetBase::SetHunger);
	Player->OnThirstUpdated.AddDynamic(StatWidget, &UStatWidgetBase::SetThirst);
	Player->OnEnergyUpdated.AddDynamic(StatWidget, &UStatWidgetBase::SetEnergy);
	Player->OnHealthUpdated.AddDynamic(StatWidget, &UStatWidgetBase::SetHealth);

	Player->AcknowledgeStatWidgetBinding();
}

void AGameplayHUDBase::Clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

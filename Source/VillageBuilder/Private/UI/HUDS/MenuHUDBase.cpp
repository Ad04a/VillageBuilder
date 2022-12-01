// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDS/MenuHUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameModes/MainMenuModeBase.h"

void AMenuHUDBase::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AMenuHUDBase::BeginPlay() IsValid(World) == false"));
		return;
	}
	AMainMenuModeBase* GameMode = Cast<AMainMenuModeBase>(UGameplayStatics::GetGameMode(World));
	if (IsValid(GameMode) == false) {
		UE_LOG(LogTemp, Error, TEXT("AMenuHUDBase::BeginPlay() IsValid(GameMode) == false"));
		return;
	}

	MainMenuWidget = CreateWidget<UStartingWidgetBase>(UGameplayStatics::GetGameInstance(World), MainMenuWidgetClass);
	if (IsValid(MainMenuWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AMenuHUDBase::BeginPlay() IsValid(MainMenuWidget) == false"));
		return;
	}

	MainMenuWidget->PlayClicked.AddDynamic(GameMode, &AMainMenuModeBase::StartGame);
	MainMenuWidget->QuitClicked.AddDynamic(GameMode, &AMainMenuModeBase::QuitGame);

	ShowMenu();
}


void AMenuHUDBase::ShowMenu()
{
	Clear();

	if (PlayerOwner && MainMenuWidget) {
		MainMenuWidget->AddToViewport();
		PlayerOwner->bShowMouseCursor = true;
		PlayerOwner->SetInputMode(FInputModeUIOnly());
	}
}


void AMenuHUDBase::Clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

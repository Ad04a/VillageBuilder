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

	ChooseSaveGameWidget = CreateWidget<UChooseSaveGameWidgetBase>(UGameplayStatics::GetGameInstance(World), ChooseSaveGameWidgetClass);
	if (IsValid(ChooseSaveGameWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AMenuHUDBase::BeginPlay() IsValid(ChooseSaveGameWidget) == false"));
		return;
	}

	NewSaveWidget = CreateWidget<UNewSaveWidgetBase>(UGameplayStatics::GetGameInstance(World), NewSaveWidgetClass);
	if (IsValid(NewSaveWidget) == false) {
		UE_LOG(LogTemp, Error, TEXT("AMenuHUDBase::BeginPlay() IsValid(NewSaveWidget) == false"));
		return;
	}

	MainMenuWidget->QuitClicked.AddDynamic(GameMode, &AMainMenuModeBase::QuitGame);

	MainMenuWidget->PlayClicked.AddDynamic(GameMode, &AMainMenuModeBase::GetAllSlots);
	GameMode->OnSaveSlotsFound.BindDynamic(this, &AMenuHUDBase::ShowChooseSaveGame);

	ChooseSaveGameWidget->OnSlotSelected.BindDynamic(GameMode, &AMainMenuModeBase::StartGame);
	ChooseSaveGameWidget->OnBackClicked.BindDynamic(this, &AMenuHUDBase::ShowMenu);
	ChooseSaveGameWidget->OnCreateClicked.BindDynamic(this, &AMenuHUDBase::ShowNewSave);
	

	NewSaveWidget->OnBackClicked.BindDynamic(this, &AMenuHUDBase::RemoveNewSave);
	NewSaveWidget->OnCreateClicked.BindDynamic(GameMode, &AMainMenuModeBase::AddSave);

	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeUIOnly());

	ShowMenu();
}


void AMenuHUDBase::ShowMenu()
{
	Clear();

	if (PlayerOwner && MainMenuWidget) 
	{
		MainMenuWidget->AddToViewport();
	}
}

void AMenuHUDBase::ShowChooseSaveGame(TArray<FString> SaveSlots)
{
	Clear();
	ChooseSaveGameWidget->Init(SaveSlots);

	if (PlayerOwner && ChooseSaveGameWidget) 
	{
		ChooseSaveGameWidget->AddToViewport();
	}
}

void AMenuHUDBase::ShowNewSave()
{
	if (NewSaveWidget->IsInViewport() == true)
	{
		return;
	}
	if (PlayerOwner && NewSaveWidget)
	{
		NewSaveWidget->AddToViewport();
	}
}

void AMenuHUDBase::RemoveNewSave()
{
	if (NewSaveWidget->IsInViewport() == true)
	{
		NewSaveWidget->RemoveFromViewport();
	}
}

void AMenuHUDBase::Clear()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

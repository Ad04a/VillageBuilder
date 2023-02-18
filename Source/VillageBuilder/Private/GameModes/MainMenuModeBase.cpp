// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/MainMenuModeBase.h"
#include "GameModes/VillageBuilderGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "HAL/FileManagerGeneric.h"
#include "VillageBuilderSaveGame.h"


void AMainMenuModeBase::StartGame(FString SlotName)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AMainMenuModeBase::StartGame() IsValid(World) == false"));
		return;
	}
	UVillageBuilderGameInstance* GameInstane = Cast<UVillageBuilderGameInstance>(World->GetGameInstance());
	if (IsValid(GameInstane) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AMainMenuModeBase::StartGame() IsValid(GameInstane) == false"));
		return;
	}
	GameInstane->SaveSlotName = SlotName;
	UGameplayStatics::OpenLevel(World, "NewWorld");
}


void AMainMenuModeBase::QuitGame()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (IsValid(PC) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AMainMenuModeBase::StartGame() IsValid(PlayerController) == false"));
		return;
	}

	PC->ConsoleCommand("quit");

}

void AMainMenuModeBase::GetAllSlots()
{
	TArray<FString> Saves;
	FString Directory = FPaths::ProjectSavedDir() + "SaveGames";
	FString Extention = ".sav";
	IFileManager::Get().FindFiles(Saves, *Directory, *Extention);
	OnSaveSlotsFound.ExecuteIfBound(Saves);
}

void AMainMenuModeBase::AddSave(FString SaveName)
{
	UVillageBuilderSaveGame* NewSave;
	NewSave = Cast<UVillageBuilderSaveGame>(UGameplayStatics::CreateSaveGameObject(UVillageBuilderSaveGame::StaticClass()));
	UGameplayStatics::SaveGameToSlot(NewSave, SaveName, 0);
	GetAllSlots();
}
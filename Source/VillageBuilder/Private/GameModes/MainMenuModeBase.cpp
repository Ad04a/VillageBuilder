// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/MainMenuModeBase.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuModeBase::StartGame()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AMainMenuModeBase::StartGame() IsValid(World) == false"));
		return;
	}

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
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "VillageBuilderSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UVillageBuilderSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	bool bIsFirstLoad = true;
};

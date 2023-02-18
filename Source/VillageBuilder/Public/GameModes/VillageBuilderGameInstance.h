// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "VillageBuilderGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VILLAGEBUILDER_API UVillageBuilderGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	FString SaveSlotName;
};

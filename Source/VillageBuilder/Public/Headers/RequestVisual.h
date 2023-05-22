#pragma once

#include "RequestVisual.generated.h"

USTRUCT(BlueprintType)
struct FVisualRequest
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	FText Villager;

	UPROPERTY(VisibleAnywhere)
	TMap<FString, int> Classes;

	UPROPERTY(VisibleAnywhere)
	bool IsFull;
};
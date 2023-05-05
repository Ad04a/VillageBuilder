#pragma once

#include "FoliageSaving.generated.h"



USTRUCT(BlueprintType)
struct FHarvestableFoliageInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<float> PerInstanceHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<int> RemovedIndexes;

};
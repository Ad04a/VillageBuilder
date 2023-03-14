#pragma once

#include "AnimalSaving.generated.h"



USTRUCT(BlueprintType)
struct FAnimalInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FTransform Position;

	inline bool operator==(const FAnimalInfoStruct& other) const
	{
		return (other.Position.GetLocation() == Position.GetLocation());
	}
	inline bool operator != (const FAnimalInfoStruct& other) const
	{
		return !( other.Position.GetLocation() == Position.GetLocation());
	}
};

USTRUCT(BlueprintType)
struct FAnimalSpawnerInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CurrentSpawnTime = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAnimalInfoStruct> Animals;

};
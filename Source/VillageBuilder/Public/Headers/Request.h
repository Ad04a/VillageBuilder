#pragma once

#include "Request.generated.h"

USTRUCT(BlueprintType)
struct FRequest
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<class AItem>> Items;

	UPROPERTY(VisibleAnywhere)
	class AVillager* Villager;

	UPROPERTY(VisibleAnywhere)
	class ABaseWorkStation* WorkStation;

	UPROPERTY(VisibleAnywhere)
	bool IsFull;

	inline bool operator==(const FRequest& other) const
	{
		return other.Items == Items && other.Villager == Villager && other.WorkStation == WorkStation && other.IsFull == IsFull;
	}
	inline bool operator != (const FRequest& other) const
	{
		return !(other.Items == Items && other.Villager == Villager && other.WorkStation == WorkStation && other.IsFull == IsFull);
	}
};


#pragma once

#include "Headers/StatAndTraitEnums.h"
#include "Engine/DataTable.h"
#include "StatAndTraitStructure.generated.h"



USTRUCT(BlueprintType)
struct FStatInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float Default = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float PerLevel = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	float Max = 50;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	float Current = Max;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float ChangeValue = 1;

};

USTRUCT(BlueprintType)
struct FTraitInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	int Level = 1;

	UPROPERTY(EditDefaultsOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Level)
	bool CanLevelUp = true;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Level)
	int CurrentXp = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Level)
	int NeededXpPerLevel = 10;
};

USTRUCT(BlueprintType)
struct FStatTraitData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Traits)
		TMap<TEnumAsByte<ETrait>, FTraitInfoStruct> TraitsMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		TMap<TEnumAsByte<EStat>, FStatInfoStruct> StatsMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
		TMap<TEnumAsByte<EStat>, TEnumAsByte<ETrait>> StatTraitRelation;
};

USTRUCT(BlueprintType)
struct FVillagerVisualInfoStruct
{
	GENERATED_BODY()

		UPROPERTY()
		FString Name;

	UPROPERTY()
		FString Profession;

	UPROPERTY()
		TMap<TEnumAsByte<ETrait>, float> TraitMap;
};


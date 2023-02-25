#pragma once

#include "StatAndTraitEnums.generated.h"

UENUM(BlueprintType)
enum ETrait {
	Vitality      UMETA(DisplayName = "Vitality"),
	Survivability UMETA(DisplayName = "Survivability"),
	Agility       UMETA(DisplayName = "Agility"),
	Strength      UMETA(DisplayName = "Strength"),
	Dexterity     UMETA(DisplayName = "Dexterity")
};
ENUM_RANGE_BY_FIRST_AND_LAST(ETrait, ETrait::Vitality, ETrait::Dexterity);

UENUM(BlueprintType)
enum EStat {
	Health  UMETA(DisplayName = "Health"),
	Energy  UMETA(DisplayName = "Energy"),
	Hunger  UMETA(DisplayName = "Hunger"),
	Thirst  UMETA(DisplayName = "Thirst"),
	Speed   UMETA(DisplayName = "Speed")
};
ENUM_RANGE_BY_FIRST_AND_LAST(EStat, EStat::Health, EStat::Speed);
#pragma once 

#include "Professions.generated.h"

UENUM(BlueprintType)
enum EProfessions {
	Passing		UMETA(DisplayName = "Passing"),
	Unemployed	UMETA(DisplayName = "Unemployed"),
	Mayor       UMETA(DisplayName = "Mayor"),
	Builder     UMETA(DisplayName = "Builder"),
	Forester    UMETA(DisplayName = "Forester"),
	Courier		UMETA(DisplayName = "Courier")
};
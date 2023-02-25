#pragma once

#include "VisualizationTypes.generated.h" 

UENUM(BlueprintType)
enum EVisualiationTypes {
	StatAndTrait UMETA(DisplayName = "StatAndTrait"),
	Inventory    UMETA(DisplayName = "Inventory"),
	Employment 	 UMETA(DisplayName = "Employment")
};

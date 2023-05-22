#pragma once

#include "VisualizationTypes.generated.h" 

UENUM(BlueprintType)
enum EVisualiationTypes {
	NoVisual	 UMETA(DisplayName = "NoVisual"),
	StatAndTrait UMETA(DisplayName = "StatAndTrait"),
	Inventory    UMETA(DisplayName = "Inventory"),
	Employment 	 UMETA(DisplayName = "Employment"),
	Options 	 UMETA(DisplayName = "Options"),
	Building 	 UMETA(DisplayName = "Building"),
	Construction UMETA(DisplayName = "Construction"),
	Spectating   UMETA(DisplayName = "Spectating"),
	Invite       UMETA(DisplayName = "Invite"),
	Request      UMETA(DisplayName = "Request"),
};

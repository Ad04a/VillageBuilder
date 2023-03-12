#pragma once

#include "AIStates.generated.h"

UENUM(BlueprintType)
enum EAIState {
	Active      UMETA(DisplayName = "Active"),
	Disabled   UMETA(DisplayName = "Disabled"),
	Dead UMETA(DisplayName = "Dead")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIStateSignature, class APawn*, ControlledPawn, EAIState, State);
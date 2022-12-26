#pragma once

#include "HandActionEnums.generated.h"

UENUM(BlueprintType)
enum EVillagerItemSlot {
	LeftHand  UMETA(DisplayName = "LeftHand"),
	RightHand UMETA(DisplayName = "RightHand")
};

UENUM(BlueprintType)
enum EHandActionType {
	Primary  UMETA(DisplayName = "Primary"),
	Secondary UMETA(DisplayName = "Secondary")
};
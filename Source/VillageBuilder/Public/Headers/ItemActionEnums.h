#pragma once

#include "ItemActionEnums.generated.h"

UENUM(BlueprintType)
enum EItemActionType {
	None      UMETA(DisplayName = "None"),
	Primary   UMETA(DisplayName = "Primary"),
	Secondary UMETA(DisplayName = "Secondary")
};

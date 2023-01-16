#pragma once

#include "ItemActionEnums.generated.h"

UENUM(BlueprintType)
enum EItemActionType {
	Primary  UMETA(DisplayName = "Primary"),
	Secondary UMETA(DisplayName = "Secondary")
};
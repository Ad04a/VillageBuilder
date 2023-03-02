#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryDropEvent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDropStartedSignature, UWidget*, DropedPoint, UObject*, Payload);
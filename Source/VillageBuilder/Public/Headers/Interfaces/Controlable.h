// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Controlable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UControlable : public UInterface
{
	GENERATED_BODY()
};

class VILLAGEBUILDER_API IControlable
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Control")
	void UpdateMovement(float MoveForwardValue, float MoveRightValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Control")
	void PawnTurnAtRate(float Rate);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Control")
	void PawnLookUpAtRate(float Rate);
};

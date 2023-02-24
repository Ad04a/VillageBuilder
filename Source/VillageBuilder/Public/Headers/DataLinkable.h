// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataLinkable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDataLinkable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VILLAGEBUILDER_API IDataLinkable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DataLink")
	TArray<class UVisualizationInfo*> InteractRequest();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DataLink")
	void BreakDataLinks();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DataLink")
	FText DisplayDataLinkText();
};

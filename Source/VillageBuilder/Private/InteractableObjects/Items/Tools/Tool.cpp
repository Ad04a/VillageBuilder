// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Items/Tools/Tool.h"

ATool::ATool()
{
	
}

void ATool::BeginPlay()
{
	Super::BeginPlay();
	LoadFromDataTable();
}

void ATool::Use(AVillager* User, EItemActionType ActionType)
{
	UE_LOG(LogTemp, Error, TEXT("ATool::Use - %s"), *GetClass()->GetName());
}

void ATool::LoadFromDataTable()
{
	Super::LoadFromDataTable();
	
	if (IsValid(SecondaryDataTable) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("ATool::LoadFromDataTable() IsValid(DataTable) == false from %s"), *GetClass()->GetName());
		return;
	}

	FToolData* ToolData = SecondaryDataTable->FindRow<FToolData>(GetClass()->GetFName(), "");

	if (ToolData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ATool::LoadFromDataTable() ToolData == nullptr from %s"), *GetClass()->GetName());
		return;
	}

	Durability = ToolData->Durability;
}
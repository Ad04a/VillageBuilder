// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Characters/Villager.h"
#include "Headers/StatAndTraitEnums.h"
#include "Tool.generated.h"

USTRUCT(BlueprintType)
struct FToolData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UNiagaraSystem* HitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETrait>  ProficiencyModifier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ProficiencyValue;

};

UCLASS()
class VILLAGEBUILDER_API ATool : public AItem
{
	GENERATED_BODY()
	
private:
	TSet<AActor*> DamagedActors;

public:
	ATool();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetIsActive(bool State) override;
	virtual void LoadFromDataTable() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tool )
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UNiagaraSystem* HitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETrait> ProficiencyModifier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ProficiencyValue;

	void GenerateHit(FVector Location);

public:


};

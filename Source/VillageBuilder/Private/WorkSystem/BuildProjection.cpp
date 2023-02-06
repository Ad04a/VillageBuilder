// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkSystem/BuildProjection.h"

// Sets default values
ABuildProjection::ABuildProjection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABuildProjection::SetInvalid);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABuildProjection::SetValid);
}

void ABuildProjection::SetMaterial(UMaterialInterface* Material)
{
	TArray<USceneComponent*>ChildrenComp;
	MeshComponent->GetChildrenComponents(true, ChildrenComp);
	MeshComponent->SetMaterial(0, Material);
	for (USceneComponent* Child : ChildrenComp)
	{
		UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(Child);
		if (IsValid(MeshComp) == false) {
			continue;
		}
		MeshComp->SetMaterial(0, Material);
	}
}

void ABuildProjection::SetValid(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsValid = true;
	SetMaterial(ValidMaterial);
}

void ABuildProjection::SetInvalid(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bIsValid = false;
	SetMaterial(InvalidMaterial);
}


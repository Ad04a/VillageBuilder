// Fill out your copyright notice in the Description page of Project Settings.


#include "Enviroment/HarvestableTree.h"
#include "Components/BoxComponent.h"

AHarvestableTree::AHarvestableTree()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
	DestroyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("DestroyCollision"));
}

void AHarvestableTree::BeginPlay()
{
	Super::BeginPlay();
	DestroyCollision->OnComponentBeginOverlap.AddDynamic(this, &AHarvestableTree::OnTreeFallen);
	DestroyCollision->SetUsingAbsoluteScale(true);
	DestroyCollision->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("destroy_collision_socket"));
	MeshComponent->SetSimulatePhysics(true);
	SetActorEnableCollision(true);
	FVector NewLocation = GetActorLocation();
	NewLocation.Z += 6;
	FVector Force = FVector(FMath::RandRange(-2.0, 2.0), FMath::RandRange(-2.0, 2.0), 0);
	MeshComponent->AddImpulse(Force*MeshComponent->GetMass()*100);
}

void AHarvestableTree::OnTreeFallen(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Component %s \nOverlapna s actor: %s, \ncomponent: %s\n s index: %d\n s bFromSweep: %d"), *OverlappedComponent->GetName(),*OtherActor->GetName(), *OtherComp->GetName(), OtherBodyIndex, bFromSweep);
	if (OtherActor ==  this || OtherComp == MeshComponent) {
		return;
	}
	Disappear();
}
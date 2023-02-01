// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/VillageMayor.h"

AVillageMayor::AVillageMayor()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	CameraComponent->bUsePawnControlRotation = true;
}

void AVillageMayor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckForInteractables();
}

void AVillageMayor::CheckForInteractables()
{
	FVector StartTrace = CameraComponent->GetComponentLocation();
	FVector EndTrace = CameraComponent->GetForwardVector() * Reach + StartTrace;

	const FName TraceTag("MyTraceTag");

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillageMayor::CheckForInteractables IsValid(World) == false"));
		return;
	}
	World->DebugDrawTraceTag = TraceTag;

	FHitResult HitResult;
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);
	CQP.TraceTag = TraceTag;


	World->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_WorldDynamic, CQP);

	IInteractable* InteractableObject = Cast<IInteractable>(HitResult.GetActor());

	if (InteractableObject == nullptr && FocusedActor != nullptr)
	{
		FocusedActor = nullptr;
		OnInteraction.Broadcast(FText());
		return;
	}
	if (Cast<IInteractable>(FocusedActor) != InteractableObject)
	{
		FocusedActor = HitResult.GetActor();
		OnInteraction.Broadcast(Cast<IInteractable>(FocusedActor)->Execute_DisplayInteractText(FocusedActor));
	}

}
void AVillageMayor::ShowTraitMenu()
{
	if (IsInteracting == false)
	{
		ToggleTraitsMenu(this);
		CanInteract = !CanInteract;
	}

}

void AVillageMayor::ToggleTraitsMenu(AVillager* Caller) {

	OnToggleTraitsMenu.Broadcast(Caller);
	IsMovementEnabled = !IsMovementEnabled;
	IsRotationEnabled = !IsRotationEnabled;
}

void AVillageMayor::Interact()
{
	if (FocusedActor != nullptr && CanInteract == true)
	{
		Cast<IInteractable>(FocusedActor)->Execute_InteractRequest(FocusedActor, this);
	}
}

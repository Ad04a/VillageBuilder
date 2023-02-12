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


	World->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_GameTraceChannel1, CQP);

	AActor* HitActor = HitResult.GetActor();
	UPrimitiveComponent* HitComponent = HitResult.GetComponent();
	IInteractable* InteractableActor = Cast<IInteractable>(HitActor);
	IInteractable* InteractableComponent = Cast<IInteractable>(HitComponent);

	if (HitActor == nullptr)
	{
		FocusedObject = nullptr;
		OnInteraction.Broadcast(FText());
		return;
	}
	if (InteractableComponent != nullptr)
	{
		FocusedObject = HitComponent;
		OnInteraction.Broadcast(InteractableComponent->Execute_DisplayInteractText(HitComponent));
		return;
	}
	if(InteractableActor == nullptr)
	{
		FocusedObject = nullptr;
		OnInteraction.Broadcast(FText());
		return;
	}
	FocusedObject = HitActor;
	OnInteraction.Broadcast(InteractableActor->Execute_DisplayInteractText(HitActor));
	

}
void AVillageMayor::ShowTraitMenu()
{
	if (bIsInteracting == false)
	{
		bIsInteracting = !bIsInteracting;
		ToggleTraitsMenu(this);
		CanInteract = !CanInteract;
	}

}

void AVillageMayor::ToggleTraitsMenu(AVillager* Caller)
{
	OnToggleTraitsMenu.Broadcast(Caller);
	ToggleStableInteraction();
}

void AVillageMayor::Interact()
{
	if (FocusedObject != nullptr && CanInteract == true)
	{
		Cast<IInteractable>(FocusedObject)->Execute_InteractRequest(FocusedObject, this);
	}
}

void AVillageMayor::ToggleEmployeeMenu(ABaseWorkStation* WorkStation)
{
	OnToggleEmployeeMenu.Broadcast(WorkStation);
	ToggleStableInteraction();
}

void AVillageMayor::ToggleStableInteraction()
{
	bCanUseItems = !bCanUseItems;
	bIsInteracting = !bIsInteracting;
	bIsMovementEnabled = !bIsMovementEnabled;
	bIsRotationEnabled = !bIsRotationEnabled;
}
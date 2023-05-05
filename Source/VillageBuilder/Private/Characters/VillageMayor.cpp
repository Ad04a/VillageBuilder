// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/VillageMayor.h"
#include "DataTransfers/DataLink.h"

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
	EmitChecker();
	
}

void AVillageMayor::EmitChecker()
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

	FHitResult HitResult;
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);
	CQP.TraceTag = TraceTag;


	World->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_GameTraceChannel1, CQP);

	CheckForInteractables(HitResult);
	CheckForDataLinks(HitResult.GetActor());
}

void AVillageMayor::CheckForInteractables(FHitResult HitResult)
{
	if (bCanInteract == false)
	{
		FocusedInteractableObject = nullptr;
		OnInteraction.Broadcast(FText());
	}

	AActor* HitActor = HitResult.GetActor();
	UPrimitiveComponent* HitComponent = HitResult.GetComponent();
	IInteractable* InteractableActor = Cast<IInteractable>(HitActor);
	IInteractable* InteractableComponent = Cast<IInteractable>(HitComponent);

	if (HitActor == nullptr)
	{
		FocusedInteractableObject = nullptr;
		OnInteraction.Broadcast(FText());
		return;
	}
	if (InteractableComponent != nullptr)
	{
		FocusedInteractableObject = HitComponent;
		OnInteraction.Broadcast(InteractableComponent->Execute_DisplayInteractText(HitComponent));
		return;
	}
	if (InteractableActor == nullptr)
	{
		FocusedInteractableObject = nullptr;
		OnInteraction.Broadcast(FText());
		return;
	}
	FocusedInteractableObject = HitActor;
	OnInteraction.Broadcast(InteractableActor->Execute_DisplayInteractText(HitActor));
}

void AVillageMayor::CheckForDataLinks(AActor* HitActor)
{
	if (bCanInteract == false)
	{
		FocusedDataLinkableObject = nullptr;
		OnDataLink.Broadcast(FText());
	}
	IDataLinkable* DataLinkableActor = Cast<IDataLinkable>(HitActor);

	if (HitActor == nullptr || DataLinkableActor == nullptr)
	{
		FocusedDataLinkableObject = nullptr;
		OnDataLink.Broadcast(FText());
		return;
	}
	FocusedDataLinkableObject = HitActor;
	OnDataLink.Broadcast(DataLinkableActor->Execute_DisplayDataLinkText(HitActor));
}

void AVillageMayor::ShowTraitMenu()
{
	UDataLink::CreateDataLink(this, nullptr);
}

void AVillageMayor::Interact()
{
	if (FocusedInteractableObject != nullptr )
	{
		Cast<IInteractable>(FocusedInteractableObject)->Execute_InteractRequest(FocusedInteractableObject, this);
	}
}

void AVillageMayor::InitiateLink()
{
	if (FocusedDataLinkableObject != nullptr)
	{
		UDataLink::CreateDataLink(this, FocusedDataLinkableObject);
	}
}

void AVillageMayor::ToggleStableInteraction()
{
	bCanUseItems = !bCanUseItems;
	bIsMovementEnabled = !bIsMovementEnabled;
	bIsRotationEnabled = !bIsRotationEnabled;
}

void AVillageMayor::UpdateMovement_Implementation(float MoveForwardValue, float MoveRightValue)
{
	if (InputEnabled() == false || bIsMovementEnabled == false)
	{
		return;
	}

	if (MoveForwardValue != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), MoveForwardValue);
	}
	if (MoveRightValue != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), MoveRightValue);
	}
}

void AVillageMayor::PawnTurnAtRate_Implementation(float Rate)
{
	if (InputEnabled() == false || bIsRotationEnabled == false)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::TurnAtRate IsValid(World) == false"));
		return;
	}

	//Functionality to move slower with lower energy

	AddControllerYawInput(Rate * World->GetDeltaSeconds());
}

void AVillageMayor::PawnLookUpAtRate_Implementation(float Rate)
{
	if (InputEnabled() == false || bIsRotationEnabled == false)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::LookUpAtRate IsValid(World) == false"));
		return;
	}

	//Functionality to turn slower with lower energy


	AddControllerPitchInput(Rate * Energy * World->GetDeltaSeconds());

}
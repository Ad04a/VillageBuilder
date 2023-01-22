// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Villager.h"



// Sets default values
AVillager::AVillager()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); 
	CameraComponent->bUsePawnControlRotation = true;
}

void AVillager::BeginPlay()
{
	Super::BeginPlay();
}



void AVillager::Init(FLoadInfoStruct InLoadInfo)
{
	if (InLoadInfo != FLoadInfoStruct())
	{
		//ItemSlots = InLoadInfo.ItemSlots;
		TraitsMap = InLoadInfo.TraitsMap;
		StatsMap = InLoadInfo.StatsMap;
		SetActorTransform(InLoadInfo.Transform);
		return;
	}
	

	//------------InitTraits--------------

	int PossibleLevel = TraitsCap; //depending on the current colony level
	TArray<TEnumAsByte<ETrait>> TraitList;
	TraitsMap.GetKeys(TraitList);
	for (TEnumAsByte<ETrait> TraitName : TraitList) {

		FTraitInfoStruct* Trait = TraitsMap.Find(TraitName);
		if (Trait == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("AVillager::Init::InitTraits IsValid(Trait) == false"));
			return;
		}
		Trait->Level = FMath::RandRange(1, PossibleLevel);
	}

	//------------InitStats--------------

	TArray<TEnumAsByte<EStat>> StatList;

	StatTraitRelation.GetKeys(StatList);
	StatTraitRelation.GenerateValueArray(TraitList);

	for (int i = 0; i < StatList.Num(); i++) {

		FStatInfoStruct* Stat = StatsMap.Find(StatList[i]);
		if (Stat == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("AVillager::Init::InitStats IsValid(Stat) == false"));
			return;
		}
		FTraitInfoStruct* Trait = TraitsMap.Find(TraitList[i]);
		if (Trait == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("AVillager::Init::InitStats IsValid(Trait) == false"));
			return;
		}
		Stat->Max = Stat->Default + Trait->Level * Stat->PerLevel;
		Stat->Current = Stat->Max;
	}


}

FLoadInfoStruct AVillager::GetSaveInfo()
{
	FLoadInfoStruct SaveInfo;
	//SaveInfo.ItemSlots = ItemSlots;
	SaveInfo.TraitsMap = TraitsMap;
	SaveInfo.StatsMap     = StatsMap;
	SaveInfo.Transform     = GetActorTransform();

	return SaveInfo;
}

void AVillager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckForInteractables();

	FStatInfoStruct* Health = StatsMap.Find(EStat::Health);
	if (Health->Current == 0) {
		Die();
	}


	StatDepletion += DeltaTime;
	if (StatDepletion >= StatDepletionInterval) {

		FStatInfoStruct* Thirst = StatsMap.Find(EStat::Thirst);
		AddStatValue(EStat::Thirst, Thirst->ChangeValue);

		if (Thirst->Current == 0) {
			AddStatValue(EStat::Health, Health->Max * -0.05);
		}

		FStatInfoStruct* Hunger = StatsMap.Find(EStat::Hunger);
		AddStatValue(EStat::Hunger, Hunger->ChangeValue);

		if (Hunger->Current == 0) {
			AddStatValue(EStat::Health, Health->Max * -0.02);
		}

		FStatInfoStruct* Energy = StatsMap.Find(EStat::Energy);
		AddStatValue(EStat::Energy, Energy->ChangeValue);

		if (Energy->Current == 0) {
			AddStatValue(EStat::Health, Health->Max * -0.01);
		}

		if (Hunger->Current > Hunger->Max * SaturationForPassiveHealing && Thirst->Current > Thirst->Max * SaturationForPassiveHealing) {

			AddStatValue(EStat::Health, Health->ChangeValue);
		}

		StatDepletion = 0;
	}

}

float AVillager::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	AddStatValue(EStat::Health, -DamageAmount);
	FStatInfoStruct* Stat = StatsMap.Find(EStat::Health);
	if (Stat == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AVillager::AddStatValue IsValid(Stat) == false"));
		return 0;
	}
	
	return -DamageAmount;
}

void AVillager::Die()
{
	UE_LOG(LogTemp, Error, TEXT("Villager is dead"));

}

void AVillager::ShowTraitMenu()
{
	if (IsInteracting == false)
	{
		ToggleTraitsMenu(this);
		CanInteract = !CanInteract;
	}
	
}

void AVillager::ToggleTraitsMenu(AVillager* Caller) {
	
	OnToggleTraitsMenu.Broadcast(Caller);
	IsMovementEnabled = !IsMovementEnabled;
	IsRotationEnabled = !IsRotationEnabled;
}

void AVillager::Interact()
{
	if (FocusedActor != nullptr && CanInteract == true)
	{
		Cast<IInteractable>(FocusedActor)->Execute_InteractRequest(FocusedActor, this);
	}
}

void AVillager::Equip(AActor* ItemToEquip)
{
	//
	AItem* NewItem = Cast<AItem>(ItemToEquip);
	if (IsValid(ItemSlot) == false) {
		NewItem->SetEnablePhysics(false);
		ItemToEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_l_Socket"));
		ItemSlot = NewItem;
		return;
	}

}

void AVillager::DropItem()
{
	if (IsValid(ItemSlot) == false)
	{
		return;
	}
	ItemSlot->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	ItemSlot->SetEnablePhysics(true);
	ItemSlot = nullptr;
}

void AVillager::ItemAction(EItemActionType ActionType)
{
	if (IsValid(ItemSlot) == false) 
	{
		return;
	}
	OnItemAction.Broadcast(ActionType);
}

void AVillager::UseItem(EItemActionType ActionType)
{
	ItemSlot->Use(this, ActionType);
}

void AVillager::CheckForInteractables()
{
	FVector StartTrace = CameraComponent->GetComponentLocation();
	FVector EndTrace = CameraComponent->GetForwardVector() * Reach + StartTrace;
	
	const FName TraceTag("MyTraceTag");

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::CheckForInteractables IsValid(World) == false"));
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

void AVillager::RecieveXP(ETrait, int XPAmount)
{


}

void AVillager::AssignJob()
{
}

void AVillager::AcknowledgeWidgetBinding()
{
	AddStatValue(EStat::Hunger, 0);
	AddStatValue(EStat::Energy, 0);
	AddStatValue(EStat::Thirst, 0);
	AddStatValue(EStat::Health, 0);

}

void AVillager::UpdateMovement(float MoveForwardValue, float MoveRightValue)
{
	if ( InputEnabled() == false || IsMovementEnabled == false)
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

void AVillager::TurnAtRate(float Rate)
{
	if (InputEnabled() == false || IsRotationEnabled == false)
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

void AVillager::LookUpAtRate(float Rate)
{
	if (InputEnabled() == false || IsRotationEnabled == false)
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


	AddControllerPitchInput(Rate *Energy * World->GetDeltaSeconds());
	
}

void AVillager::AddStatValue(EStat StatName, float InValue)
{
	FStatInfoStruct* Stat = StatsMap.Find(StatName);
	if (Stat == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AVillager::AddStatValue IsValid(Stat) == false"));
		return;
	}
	
	Stat->Current = FMath::Clamp(Stat->Current+InValue, 0, Stat->Max);

	OnStatUpdated.Broadcast(StatName,Stat->Current, Stat->Max);
}

int AVillager::GetTrait(ETrait TraitName)
{
	FTraitInfoStruct* Trait = TraitsMap.Find(TraitName);
	if (Trait == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("AVillager::GetTrait IsValid(Trait) == false"));
		return 0;
	}

	return Trait->Level;
}

void AVillager::InteractRequest_Implementation(class AActor* InteractingActor)
{
	AVillager* InteractingVillager = Cast<AVillager>(InteractingActor);
	if (IsValid(InteractingVillager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AVillager::InteractRequest_Implementation IsValid(InteractingVillager) == false"));
		return;
	}
	InteractingVillager->ToggleTraitsMenu(this);
	InteractingVillager->IsInteracting = !InteractingVillager->IsInteracting;
}

FText AVillager::DisplayInteractText_Implementation()
{
	return FText::FromString( "Talk with Villager" );//Add name variable
}

EItemType AVillager::GetEquipItemType()
{
	if (ItemSlot == nullptr)
	{
		return EItemType::Default;
	}
	return ItemSlot->GetItemType();
}

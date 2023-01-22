// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Villager/ItemUseNotify.h"
#include "Characters/Villager.h"

void UItemUseNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{

	if (IsValid(MeshComp->GetOwner()) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UItemUseNotifyState::NotifyBegin IsValid(MeshComp->GetOwner()) == false"));
		return;
	}
	AVillager* Villager = Cast<AVillager>(MeshComp->GetOwner());
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UItemUseNotifyState::NotifyBegin IsValid(Villager) == false"));
		return;
	}
	Villager->UseItem(ActionType);
}


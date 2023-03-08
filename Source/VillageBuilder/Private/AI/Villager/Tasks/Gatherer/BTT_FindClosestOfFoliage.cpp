// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Villager/Tasks/Gatherer/BTT_FindClosestOfFoliage.h"
#include "AI/Villager/VillagerAIController.h"
#include "Characters/Villager.h"

#include "EngineUtils.h"
#include "Runtime/Foliage/Public/InstancedFoliageActor.h"

UBTT_FindClosestOfFoliage::UBTT_FindClosestOfFoliage()
{
    NodeName = "FindClosestOfFoliage";
}


EBTNodeResult::Type UBTT_FindClosestOfFoliage::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	AVillagerAIController* Controller = Cast<AVillagerAIController>(OwnerComponent.GetAIOwner());
	if (IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_FindClosestOfFoliage::ExecuteTask IsValid(Controller) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackBoard = Controller->GetBlackboard();
	if (IsValid(BlackBoard) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_FindClosestOfFoliage::ExecuteTask IsValid(BlackBoard) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	AVillager* Villager = Controller->GetControlledVillager();
	if (IsValid(Villager) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UBTT_FindClosestOfFoliage::ExecuteTask IsValid(Villager) == false"));
		FinishLatentTask(OwnerComponent, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	FVector ClosestLocation = FVector();
	FVector CheckLocation = FVector();

	for (TActorIterator<AInstancedFoliageActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AInstancedFoliageActor* FoliageMesh = *ActorItr;
		auto FoliageComponents = FoliageMesh->GetComponentsByTag(UFoliageInstancedStaticMeshComponent::StaticClass(), TagToSearch);
		for (auto& Comp : FoliageComponents)
		{
			auto FoliageComponent = Cast<UFoliageInstancedStaticMeshComponent>(Comp);
			if (FoliageComponent == nullptr)
			{
				continue;
			}
			int InstanceCount = FoliageComponent->GetInstanceCount();
			if (InstanceCount < 1)
			{
				continue;
			}
			FTransform InstanceTransform;
			FoliageComponent->GetInstanceTransform(0, InstanceTransform, true);
			float ClosestDistance = FVector::Distance(Villager->GetActorLocation(), InstanceTransform.GetLocation());
			ClosestLocation = InstanceTransform.GetLocation();

			for (int i = 1; i < InstanceCount; ++i)
			{
				
				FoliageComponent->GetInstanceTransform(i, InstanceTransform, true);
				float TempDistance = FVector::Distance(Villager->GetActorLocation(), InstanceTransform.GetLocation());
				if (TempDistance >= ClosestDistance)
				{
					continue;
				}
				ClosestDistance = TempDistance;
				ClosestLocation = InstanceTransform.GetLocation();
			}
		}
	}

	if (ClosestLocation == CheckLocation)
	{
		BlackBoard->ClearValue(WriteInto.SelectedKeyName);
	}
	else
	{
		BlackBoard->SetValueAsVector(WriteInto.SelectedKeyName, ClosestLocation);
	}

    FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}


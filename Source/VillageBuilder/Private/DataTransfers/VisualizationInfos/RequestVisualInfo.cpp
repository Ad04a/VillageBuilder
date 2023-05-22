// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTransfers/VisualizationInfos/RequestVisualInfo.h"
#include "WorkSystem/VillageManager.h"
#include "Items/Item.h"

#include "Headers/Request.h"

UVisualizationInfo* URequestVisualInfo::CreateVisualInfo(AActor* InActor)
{
	URequestVisualInfo* Info = NewObject<URequestVisualInfo>();
	if (IsValid(Info) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("URequestVisualInfo::CreateVisualInfo Cannot create info"));
		return nullptr;
	}
	UWorld* World = InActor->GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("URequestVisualInfo::CreateVisualInfo IsValid(World) == false"));
		return nullptr;
	}

	AVillageManager* Village = Cast<AVillageManager>(InActor);

	Village->OnRequestsUpdated.AddDynamic(Info, &URequestVisualInfo::RecieveUpdate);
	Info->OnGetUpdates.BindDynamic(Village, &AVillageManager::SendRequests);

	return Info;
}

void URequestVisualInfo::RecieveUpdate(TArray<FRequest> Requests)
{
	TArray<FVisualRequest> VisualRequests;

	for (FRequest Request : Requests)
	{
		FText Villager = FText::FromString(Request.Villager->GetName());
		TMap<FString, int> Classes;

		for (TSubclassOf<AItem> Item : Request.Items)
		{
			int Value = Classes.Contains(Item->GetName()) ? *Classes.Find(Item->GetName()) : 0;
			Classes.Emplace(Item->GetName(), Value + 1);
		}

		FVisualRequest VisualRequest;
		VisualRequest.Villager = Villager;
		VisualRequest.Classes = Classes;
		VisualRequest.IsFull = Request.IsFull;
		VisualRequests.Add(VisualRequest);
	}


	OnRequestUpdated.ExecuteIfBound(VisualRequests);
}

void URequestVisualInfo::GetUpdate()
{
	OnGetUpdates.ExecuteIfBound();
}

void URequestVisualInfo::Clear()
{
	OnGetUpdates.Unbind();
	Super::Clear();
}
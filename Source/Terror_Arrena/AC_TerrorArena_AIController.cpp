// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_TerrorArena_AIController.h"

#include "EnemiesBaseClass.h"
#include "WeaponComponent.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void AAC_TerrorArena_AIController::BeginPlay()
{
	Super::BeginPlay();


	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AAC_TerrorArena_AIController::StartChasing, 0.5, true);
}

void AAC_TerrorArena_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (InPawn)
	{
		WeaponComponentRef = InPawn->FindComponentByClass<UWeaponComponent>();
	}
}

void AAC_TerrorArena_AIController::StartChasing()
{
	AGameStateBase* MyGS = GetWorld()->GetGameState();
	if (MyGS)
	{
		APawn* ClosestPawn = nullptr;
		float ClosestDistance = FLT_MAX;

		MyGS->PlayerArray;
		for (int32 i = 0; i < MyGS->PlayerArray.Num(); i++)
		{
			APlayerState* PlayerState = MyGS->PlayerArray[i];
			APawn* PlayerPawn = PlayerState ? PlayerState->GetPawn() : nullptr;

			if (PlayerPawn)
			{
				float Distance = PlayerPawn->GetDistanceTo(GetPawn());
				if (Distance < ClosestDistance)
				{
					ClosestDistance = Distance;
					ClosestPawn = PlayerPawn;
				}
			}
		}
		if (WeaponComponentRef)
		{
			if (WeaponComponentRef->WeaponAsset)
			{
				if (ClosestDistance >= WeaponComponentRef->WeaponAsset->Range)
				{
					MoveToActor(ClosestPawn);
					EPathFollowingRequestResult::Type Result = MoveToActor(
						ClosestPawn, WeaponComponentRef->WeaponAsset->Range - 50.f);
				}
				else
				{
					WeaponComponentRef->Fire();
				}
			}
		}
	}
}

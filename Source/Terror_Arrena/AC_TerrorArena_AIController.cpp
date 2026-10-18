// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_TerrorArena_AIController.h"

#include "EnemiesBaseClass.h"
#include "WeaponComponent.h"
#include "Kismet/GameplayStatics.h"

void AAC_TerrorArena_AIController::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AAC_TerrorArena_AIController::StartChasing, 2.0f, true);
}

void AAC_TerrorArena_AIController::StartChasing()
{
	APawn* PlayerPawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (PlayerPawn)
	{
		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn)
		{
			UWeaponComponent* Weapon = GetPawn()->FindComponentByClass<UWeaponComponent>();
			if (Weapon)
			{
				if (Weapon->WeaponAsset)
				{
					float Distance = ControlledPawn->GetDistanceTo(PlayerPawn);

					if (Distance >= Weapon->WeaponAsset->Range)
					{
						MoveToActor(PlayerPawn);
						EPathFollowingRequestResult::Type Result = MoveToActor(
							PlayerPawn, Weapon->WeaponAsset->Range - 50.f);
					}
					else
					{
						Weapon->Fire();
					}
				}
			}
		}
	}
}

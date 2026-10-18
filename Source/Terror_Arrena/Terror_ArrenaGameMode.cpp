// Copyright Epic Games, Inc. All Rights Reserved.

#include "Terror_ArrenaGameMode.h"
#include "NavigationSystem.h"
#include "GameStateTerrorArena.h"


ATerror_ArrenaGameMode::ATerror_ArrenaGameMode()
{
}

void ATerror_ArrenaGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartWave();
	AGameStateTerrorArena* GS = GetWorld()->GetGameState<AGameStateTerrorArena>();
	if (GS)
	{
		GS->RemainingEnemies = EnemiesPerWave;
		GS->OnRep_RemainingEnemies();
	}
	SpawnEnemy();
	
}

void ATerror_ArrenaGameMode::StartWave()
{
	AGameStateTerrorArena* GS = GetWorld()->GetGameState<AGameStateTerrorArena>();
	if (GS)
	{
		GS->CurrentWave++;
		GS->RemainingEnemies = EnemiesPerWave * GS->CurrentWave;
		GS->OnRep_RemainingEnemies();
	}
}

void ATerror_ArrenaGameMode::SpawnEnemy()
{
	if (EnemiesClass)
	{
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());


		AGameStateTerrorArena* GS = GetWorld()->GetGameState<AGameStateTerrorArena>();
		if (GS)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;


			for (int i = 0; i < GS->RemainingEnemies; ++i)
			{
				if (NavSys)
				{
					FNavLocation RandomPoint;
					NavSys->GetRandomReachablePointInRadius(FVector::ZeroVector, 3000.f, RandomPoint);

					FVector SpawnLocation = RandomPoint.Location;
					SpawnLocation.Z = 200.f;

					FRotator SpawnRotation = FRotator::ZeroRotator;


					FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation);

					AEnemiesBaseClass* SpawnedEnemy = GetWorld()->SpawnActor<AEnemiesBaseClass>(
						EnemiesClass, SpawnTransform, SpawnParams);
					if (SpawnedEnemy)
					{
						Enemies.Add(SpawnedEnemy);
					}
				}
			}
		}
	}
}

void ATerror_ArrenaGameMode::OnEnemyDied(AEnemiesBaseClass* DeadEnemy)
{
	Enemies.Remove(DeadEnemy);

	AGameStateTerrorArena* GS = GetWorld()->GetGameState<AGameStateTerrorArena>();
	if (GS)
	{
		GS->RemainingEnemies = Enemies.Num();
		GS->OnRep_RemainingEnemies();

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
		                                 FString::Printf(TEXT("Remaining enemies: %d"), GS->RemainingEnemies));
		if (GS->RemainingEnemies == 0)
		{
			StartWave();
			SpawnEnemy();
		}
	}
}

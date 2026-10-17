// Copyright Epic Games, Inc. All Rights Reserved.

#include "Terror_ArrenaGameMode.h"

#include "GameStateTerrorArena.h"

ATerror_ArrenaGameMode::ATerror_ArrenaGameMode()
{
}

void ATerror_ArrenaGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartWave();

	SpawnEnemy();
}

void ATerror_ArrenaGameMode::StartWave()
{
	AGameStateTerrorArena* GS = GetWorld()->GetGameState<AGameStateTerrorArena>();
	if (GS)
	{
		GS->CurrentWave++;
		GS->RemainingEnemies = EnemiesPerWave * GS->CurrentWave;
	}
}

void ATerror_ArrenaGameMode::SpawnEnemy()
{
	if (EnemiesClass)
	{
		AGameStateTerrorArena* GS = GetWorld()->GetGameState<AGameStateTerrorArena>();
		if (GS)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			FVector SpawnLocation = FVector(0.0f, 0.0f, 250.0f);

			FRotator SpawnRotation = FRotator::ZeroRotator;

			FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation);

			for (int i = 0; i < GS->RemainingEnemies; ++i)
			{
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

void ATerror_ArrenaGameMode::OnEnemyDied(AEnemiesBaseClass* DeadEnemy)
{
	
	Enemies.Remove(DeadEnemy);
	
	AGameStateTerrorArena* GS = GetWorld()->GetGameState<AGameStateTerrorArena>();
	if (GS)
	{
		GS->RemainingEnemies = Enemies.Num();
		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
										 FString::Printf(TEXT("Remaining enemies: %d"), GS->RemainingEnemies));
		if (GS->RemainingEnemies == 0)
		{
			StartWave();
			SpawnEnemy();
		}
	}
}

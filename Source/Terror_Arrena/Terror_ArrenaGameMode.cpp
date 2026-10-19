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
	
	MyGS = GetGameState<AGameStateTerrorArena>();
	
	StartWave();
	
	if (MyGS)
	{
		MyGS->RemainingEnemies = EnemiesPerWave;
		MyGS->OnRep_RemainingEnemies();
	}
	SpawnEnemy();
	
}

void ATerror_ArrenaGameMode::StartWave()
{
	if (MyGS)
	{
		MyGS->CurrentWave++;
		MyGS->RemainingEnemies = EnemiesPerWave * MyGS->CurrentWave;
		MyGS->OnRep_RemainingEnemies();
		MyGS->OnRep_WaveChanged();
	}
}

void ATerror_ArrenaGameMode::SpawnEnemy()
{
	if (EnemiesClass)
	{
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
		
		if (MyGS)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;


			for (int i = 0; i < MyGS->RemainingEnemies; ++i)
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

	if (MyGS)
	{
		MyGS->RemainingEnemies = Enemies.Num();
		MyGS->OnRep_RemainingEnemies();
		
		if (MyGS->RemainingEnemies == 0)
		{
			StartWave();
			SpawnEnemy();
			
		}
	}
}

void ATerror_ArrenaGameMode::OnPlayerDied(AController* PlayerController)
{
	FTimerHandle RespawnDelayHandleTimer;
	
	FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(this,&ATerror_ArrenaGameMode::RestartPlayer,PlayerController);
	
	GetWorld()->GetTimerManager().SetTimer(RespawnDelayHandleTimer,RespawnDelegate,RespawnDelay,false);
	
}






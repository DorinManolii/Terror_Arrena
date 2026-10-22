// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "EnemiesBaseClass.h"
#include "GameStateTerrorArena.h"
#include "Terror_ArrenaPlayerController.h"

#include "Terror_ArrenaGameMode.generated.h"

/**
 *  Simple Game Mode for a top-down perspective game
 *  Sets the default gameplay framework classes
 *  Check the Blueprint derived class for the set valuesw
 */
UCLASS(abstract)
class ATerror_ArrenaGameMode : public AGameMode
{
	GENERATED_BODY()
	/** Constructor */
public:
	
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<AGameStateTerrorArena> MyGS;
	
	
	
	ATerror_ArrenaGameMode();
	
	UPROPERTY(EditDefaultsOnly)
	int32 EnemiesPerWave = 5;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<AEnemiesBaseClass> EnemiesClass;
	
	UPROPERTY(EditDefaultsOnly)
	int32 MinPlayers = 2;
	
	virtual bool ReadyToStartMatch_Implementation() override;
	
	virtual void HandleMatchHasStarted() override;
	
	virtual void HandleMatchHasEnded() override;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerSettings")
	float RespawnDelay = 3.f;
	
	
	void StartWave();
	
	void SpawnEnemy();
	
	UPROPERTY(BlueprintReadOnly)
	TArray<AEnemiesBaseClass*> Enemies;
	
	UPROPERTY()
	TArray<TObjectPtr<AController>> DeadPlayers;
	
	void OnEnemyDied(AEnemiesBaseClass* DeadEnemy);
	
	void OnPlayerDied(AController* PlayerController);
	
	
};




// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemiesBaseClass.h"
#include "Terror_ArrenaGameMode.generated.h"

/**
 *  Simple Game Mode for a top-down perspective game
 *  Sets the default gameplay framework classes
 *  Check the Blueprint derived class for the set valuesw
 */
UCLASS(abstract)
class ATerror_ArrenaGameMode : public AGameModeBase
{
	GENERATED_BODY()
	/** Constructor */
public:
	
	virtual void BeginPlay() override;
	
	ATerror_ArrenaGameMode();
	
	UPROPERTY(EditDefaultsOnly)
	int32 EnemiesPerWave = 5;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<AEnemiesBaseClass> EnemiesClass;
	
	UFUNCTION(BlueprintCallable)
	void StartWave();
	
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();
	
	UPROPERTY(BlueprintReadOnly)
	TArray<AEnemiesBaseClass*> Enemies;
	
	void OnEnemyDied(AEnemiesBaseClass* DeadEnemy);
	
	
};




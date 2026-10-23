// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameStateTerrorArena.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemainingEnemiesChanged, int32, NewCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveChanged, int32, NewWave);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEnded);

UCLASS()


class TERROR_ARRENA_API AGameStateTerrorArena : public AGameState
{
	GENERATED_BODY()
	
	public:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintAssignable)
	FOnRemainingEnemiesChanged OnRemainingEnemiesChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnWaveChanged OnWaveChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnGameEnded OnGameEnded;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_WaveChanged)
	int32 CurrentWave = 0;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_RemainingEnemies)
	int32 RemainingEnemies = 0;
	
	virtual void OnRep_MatchState() override;
	
	UFUNCTION()
	void OnRep_RemainingEnemies();
	
	UFUNCTION()
	void OnRep_WaveChanged();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateTerrorArena.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemainingEnemiesChanged, int32, NewCount);


UCLASS()


class TERROR_ARRENA_API AGameStateTerrorArena : public AGameStateBase
{
	GENERATED_BODY()
	
	public:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintAssignable)
	FOnRemainingEnemiesChanged OnRemainingEnemiesChanged;
	
	UPROPERTY(BlueprintReadOnly,Replicated)
	int32 CurrentWave = 0;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_RemainingEnemies)
	int32 RemainingEnemies = 0;
	
	UFUNCTION()
	void OnRep_RemainingEnemies();
};

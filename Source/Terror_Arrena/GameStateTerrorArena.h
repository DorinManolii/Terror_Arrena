// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateTerrorArena.generated.h"

/**
 * 
 */
UCLASS()
class TERROR_ARRENA_API AGameStateTerrorArena : public AGameStateBase
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	public:
	
	UPROPERTY(BlueprintReadOnly,Replicated)
	int32 CurrentWave = 0;
	
	UPROPERTY(BlueprintReadOnly,Replicated)
	int32 RemainingEnemies = 0;
	
};

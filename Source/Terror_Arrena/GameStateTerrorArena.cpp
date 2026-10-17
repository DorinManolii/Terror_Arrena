// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateTerrorArena.h"
#include "Net/UnrealNetwork.h"

void AGameStateTerrorArena::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AGameStateTerrorArena, CurrentWave);
	DOREPLIFETIME(AGameStateTerrorArena, RemainingEnemies);
}

	

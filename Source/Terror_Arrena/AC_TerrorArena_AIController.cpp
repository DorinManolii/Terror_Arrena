// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_TerrorArena_AIController.h"

#include "Kismet/GameplayStatics.h"

void AAC_TerrorArena_AIController::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AAC_TerrorArena_AIController::StartChasing, 2.0f, false);
	
}

void AAC_TerrorArena_AIController::StartChasing()
{
	APawn* PlayerPawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (PlayerPawn)
	{
		MoveToActor(PlayerPawn);
		
		EPathFollowingRequestResult::Type Result = MoveToActor(PlayerPawn);
	}
}
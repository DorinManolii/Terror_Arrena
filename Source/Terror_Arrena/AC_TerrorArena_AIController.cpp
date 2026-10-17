// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_TerrorArena_AIController.h"

#include "EnemiesBaseClass.h"
#include "Kismet/GameplayStatics.h"

void AAC_TerrorArena_AIController::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Start Chasing"));
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AAC_TerrorArena_AIController::StartChasing, 2.0f, true);

	
}

void AAC_TerrorArena_AIController::StartChasing()
{
	
	APawn* PlayerPawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (PlayerPawn)
	{
		
		APawn* ControlledPawn= GetPawn();
		if (ControlledPawn)
		{
			float Distance = ControlledPawn->GetDistanceTo(PlayerPawn);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Distance: %f"), Distance));
			if (Distance >= DistanceToChasing)
			{
				MoveToActor(PlayerPawn);
				EPathFollowingRequestResult::Type Result = MoveToActor(PlayerPawn);
			}
		}

	}
}
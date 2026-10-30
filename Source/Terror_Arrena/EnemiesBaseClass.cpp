// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesBaseClass.h"

#include "AC_TerrorArena_AIController.h"
#include "HealthComponent.h"
#include "Terror_ArrenaGameMode.h"

// Sets default values
AEnemiesBaseClass::AEnemiesBaseClass()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AAC_TerrorArena_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
}

// Called when the game starts or when spawned
void AEnemiesBaseClass::BeginPlay()
{
	Super::BeginPlay();
	
	UHealthComponent* HealthComp = FindComponentByClass<UHealthComponent>();
	if (HealthComp)
	{
		HealthComp->OnDeath.AddDynamic(this, &AEnemiesBaseClass::Die);
	}
}

void AEnemiesBaseClass::Die()
{
	ATerror_ArrenaGameMode* MyGm = Cast<ATerror_ArrenaGameMode>(GetWorld()->GetAuthGameMode());
	if(MyGm)
	{
		MyGm->OnEnemyDied(this);
	}
	Destroy();
}


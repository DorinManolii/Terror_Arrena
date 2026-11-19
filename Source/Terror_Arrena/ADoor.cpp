// Fill out your copyright notice in the Description page of Project Settings.

#include "Net/UnrealNetwork.h"
#include "ADoor.h"

void AADoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);\
	DOREPLIFETIME(AADoor, bIsOpen);
}

// Sets default values
AADoor::AADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AADoor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AADoor::Rep_IsOpen()
{
	OnDoorStateChange(bIsOpen);
	
if (bIsOpen)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Open"));
}
else
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Closed"));
}
}

void AADoor::Interact_Implementation(AActor* Interactor)
{
	Super::Interact_Implementation(Interactor);
	if (!Interactor)return;
	
		bIsOpen = !bIsOpen;
		Rep_IsOpen();
}

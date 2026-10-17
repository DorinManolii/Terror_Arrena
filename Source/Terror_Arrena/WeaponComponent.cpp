// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponComponent::Fire()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		FVector ActorLocation = OwnerPawn->GetActorLocation();
		FVector ActorForwardVector = OwnerPawn->GetActorForwardVector();

		FVector Start = ActorLocation + (ActorForwardVector * 100.f);
		FVector End = Start + (ActorForwardVector * 1000.f);

		FHitResult Hit;

		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera);
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 1.0f);

		AActor* TargetActor = Hit.GetActor();

		if (TargetActor)
		{
			UGameplayStatics::ApplyDamage(TargetActor, 100.f, OwnerPawn->GetController(), OwnerPawn,
			                              UDamageType::StaticClass());
		}
	}
}

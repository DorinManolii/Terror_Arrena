// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "Interactable.h"
#include "Terror_Arrena.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UInteractionComponent::TryInteract()
{
	FVector ActorLocation = GetOwner()->GetActorLocation();
	FVector ActorForwardVector = GetOwner()->GetActorForwardVector();

	FVector Start = ActorLocation + (ActorForwardVector * 100.f);
	FVector End = Start + (ActorForwardVector * InteractDistance);

	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Interaction);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 1.0f);

	AActor* TargetActor = Hit.GetActor();

	if (TargetActor && TargetActor->Implements<UInteractable>())
	{
		IInteractable::Execute_Interact(TargetActor, GetOwner());
	}
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

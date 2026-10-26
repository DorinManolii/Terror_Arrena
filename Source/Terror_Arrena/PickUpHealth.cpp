// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpHealth.h"

#include "HealthComponent.h"
#include "Terror_ArrenaCharacter.h"

bool APickUpHealth::CanPickUp(AActor* Picker) const
{
	ATerror_ArrenaCharacter* PlayerCharacter = Cast<ATerror_ArrenaCharacter>(Picker);
	if (PlayerCharacter)
	{
		UHealthComponent* HealthComponent = PlayerCharacter->FindComponentByClass<UHealthComponent>();
		if (HealthComponent)
		{
			if (!HealthComponent->IsPlayerDied() && !HealthComponent->IsHealthFull())
			{
				return true;
			}
		}
	}
	return false;
}

void APickUpHealth::ApplyPickUp(AActor* Picker)
{
	UHealthComponent* HealthComponent = Picker->FindComponentByClass<UHealthComponent>();

	if (HealthComponent)
	{
		if (!HealthComponent->IsHealthFull())
			HealthComponent->AddHealth(HealthAmount);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			                                 FString::Printf(TEXT("Health: %s , %f"), *Picker->GetName(),HealthAmount));
		}
	}
}

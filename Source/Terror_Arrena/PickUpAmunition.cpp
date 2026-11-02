// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpAmunition.h"
#include "WeaponDataAsset.h"
#include "HealthComponent.h"
#include "Terror_ArrenaCharacter.h"
#include "WeaponComponent.h"

bool APickUpAmunition::CanPickUp(AActor* Picker) const
{
	ATerror_ArrenaCharacter* PlayerCharacter = Cast<ATerror_ArrenaCharacter>(Picker);
	if (PlayerCharacter)
	{
		UHealthComponent* HealthComponent = PlayerCharacter->FindComponentByClass<UHealthComponent>();
		if (HealthComponent)
		{
			UWeaponComponent* WeaponComponent = PlayerCharacter->FindComponentByClass<UWeaponComponent>();
			if (WeaponComponent && WeaponComponent->WeaponAsset)
			{
				if (!HealthComponent->IsPlayerDied())
				{
					if (WeaponComponent->WeaponAsset->MaxCargoAmmo > WeaponComponent->ReserveAmmo)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("CanPick"));
						return true;
						
					}
				}
			}
		}
	}
	return false;
}

void APickUpAmunition::ApplyPickUp(AActor* Picker)
{
	ATerror_ArrenaCharacter* PlayerCharacter = Cast<ATerror_ArrenaCharacter>(Picker);
	if (PlayerCharacter)
	{
		UWeaponComponent* WeaponComponent = PlayerCharacter->FindComponentByClass<UWeaponComponent>();
		if (WeaponComponent && WeaponComponent->WeaponAsset)
		{
			WeaponComponent->AddBullets(BulletsAmount);
		}
	}
}

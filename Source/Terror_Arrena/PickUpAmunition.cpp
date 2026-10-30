// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpAmunition.h"

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
			if (WeaponComponent->WeaponAsset->MaxCargoAmmo >= WeaponComponent->ReserveAmmo)
			{
			WeaponComponent->AddBullets(BulletsAmount);
			}
		}
	}
}

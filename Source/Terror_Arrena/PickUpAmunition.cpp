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
					if (!WeaponComponent->IsReserveFull())
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
			WeaponComponent->AddBullets(BulletsAmount);
		}
	}
}

void APickUpAmunition::SetBulletsAmount(int32 NewBulletsAmount)
{
	if (NewBulletsAmount <= 0)return;
	BulletsAmount = NewBulletsAmount;
}

void APickUpAmunition::SetLifeTime()
{
	SetLifeSpan(LifeTime);
}

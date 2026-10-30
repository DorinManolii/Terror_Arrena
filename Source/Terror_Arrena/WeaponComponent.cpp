// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponComponent.h"
#include "DrawDebugHelpers.h"
#include "HealthComponent.h"
#include "Terror_Arrena.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

void UWeaponComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponComponent, CurrentBullets);
	DOREPLIFETIME(UWeaponComponent, ReserveAmmo);
}

void UWeaponComponent::OnRep_ReserveAmmo()
{
	OnAmmoChanged.Broadcast();
}

void UWeaponComponent::OnRep_CurrentBullets()
{
	OnAmmoChanged.Broadcast();
}

void UWeaponComponent::Reload()
{
	if (!GetOwner()->HasAuthority()) return;
	if (!WeaponAsset) return;
	
	if (WeaponAsset->MaxAmmo == CurrentBullets)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Ammo Is full"));
		return;
	}


	if (ReserveAmmo == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("No ammo reserve"));
		return;
	}

	int32 NeedBullets = WeaponAsset->MaxAmmo - CurrentBullets;

	if (NeedBullets <= ReserveAmmo)
	{
		CurrentBullets += NeedBullets;
		ReserveAmmo -= NeedBullets;
	}
	else
	{
		CurrentBullets += ReserveAmmo;
		ReserveAmmo = 0;
	}
	OnAmmoChanged.Broadcast();
}

void UWeaponComponent::AddBullets(int32 Amount)
{
	if (!WeaponAsset)return;
	
	int32 AddAmount = FMath::Clamp(Amount + ReserveAmmo, 0, WeaponAsset->MaxCargoAmmo);
	
	ReserveAmmo = AddAmount;
	
	OnRep_ReserveAmmo();
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority())
	{
		if (WeaponAsset)
		{
			CurrentBullets = WeaponAsset->MaxAmmo;
		}
	}
}

void UWeaponComponent::Fire()
{
	if (bCanFire && CurrentBullets > 0)
	{
		CurrentBullets--;
		OnRep_CurrentBullets();

		bCanFire = false;

		APawn* OwnerPawn = Cast<APawn>(GetOwner());
		if (OwnerPawn)
		{
			if (WeaponAsset)
			{
				GetWorld()->GetTimerManager().SetTimer(CanFireTimerHandler, this, &UWeaponComponent::CanFire,
				                                       WeaponAsset->FireRate, false);

				FVector ActorLocation = OwnerPawn->GetActorLocation();
				FVector ActorForwardVector = OwnerPawn->GetActorForwardVector();

				FVector Start = ActorLocation + (ActorForwardVector * 100.f);
				FVector End = Start + (ActorForwardVector * WeaponAsset->Range);

				FHitResult Hit;

				GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Bullet);
				DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 1.0f);

				AActor* TargetActor = Hit.GetActor();

				if (TargetActor)
				{
					UHealthComponent* TargetHealth = TargetActor->FindComponentByClass<UHealthComponent>();
					if (TargetHealth)
					{
						UHealthComponent* OwnerHealth = GetOwner()->FindComponentByClass<UHealthComponent>();
						if (OwnerHealth)
						{
							if (TargetHealth->TeamTag != OwnerHealth->TeamTag || WeaponAsset->bFriendlyFire)
							{
								UGameplayStatics::ApplyDamage(TargetActor, WeaponAsset->Damage,
								                              OwnerPawn->GetController(),
								                              OwnerPawn,
								                              UDamageType::StaticClass());
							}
						}
					}
				}
			}
		}
	}
}

void UWeaponComponent::CanFire()
{
	bCanFire = true;
}

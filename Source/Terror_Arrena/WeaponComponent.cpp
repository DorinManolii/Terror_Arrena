// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponComponent.h"
#include "DrawDebugHelpers.h"
#include "Terror_Arrena.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponComponent::Fire()
{
	if (bCanFire)
	{
		bCanFire = false;

		APawn* OwnerPawn = Cast<APawn>(GetOwner());
		if (OwnerPawn)
		{
			if (WeaponAsset)
			{
				GetWorld()->GetTimerManager().SetTimer(CanFireTimerHandler, this, &UWeaponComponent::CanFire,
				                                       WeaponAsset->FireRate, true);

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
					if (!WeaponAsset->bFriendlyFire)
					{
						for (int i = 0; i < TargetActor->Tags.Num(); i++)
						{
							if (TargetActor->Tags[i].ToString().StartsWith("Team"))
							{
								FName TargetTag = TargetActor->Tags[i];

								if (!GetOwner()->Tags.Contains(TargetTag))
								{
									UGameplayStatics::ApplyDamage(TargetActor, WeaponAsset->Damage,
									                              OwnerPawn->GetController(),
									                              OwnerPawn,
									                              UDamageType::StaticClass());
								}
							}
						}
					}
					else
					{
						UGameplayStatics::ApplyDamage(TargetActor, WeaponAsset->Damage,
						                              OwnerPawn->GetController(),
						                              OwnerPawn,
						                              UDamageType::StaticClass());

						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("FriendlyFire"));
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

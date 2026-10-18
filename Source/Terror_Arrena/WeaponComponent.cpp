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

				GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera);
				DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 1.0f);

				AActor* TargetActor = Hit.GetActor();

				if (TargetActor)
				{
					UGameplayStatics::ApplyDamage(TargetActor, WeaponAsset->Damage, OwnerPawn->GetController(),
					                              OwnerPawn,
					                              UDamageType::StaticClass());
				}
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Reloading"));
	}
}

void UWeaponComponent::CanFire()
{
	bCanFire = true;
}

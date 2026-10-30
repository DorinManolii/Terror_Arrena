// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Net/UnrealNetwork.h"


void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, Health);
}

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	SetIsReplicatedByDefault(true);
}



// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamage);
}


void UHealthComponent::AddHealth(float NewHealth)
{
	if (Health <= 0)
		return;
	Health = FMath::Clamp(Health + NewHealth, 0.0f, MaxHealth);
	OnRep_Health();
}


void UHealthComponent::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                    AController* InstigatedBy, AActor* DamageCauser)
{
	if (Health <= 0)
		return;
	
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnRep_Health();

	if (Health <= 0.0f)
	{
		OnDeath.Broadcast();
	}
}

void UHealthComponent::OnRep_Health()
{
	OnHealthChanged.Broadcast(Health);
}

bool UHealthComponent::IsPlayerDied() const
{
	return Health <= 0.0f;
}

bool UHealthComponent::IsHealthFull() const
{
	return Health >= MaxHealth;
}
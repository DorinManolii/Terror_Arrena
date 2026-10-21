// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TERROR_ARRENA_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Sets default values for this component's properties
	UHealthComponent();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag TeamTag;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Health)
	float Health;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly);
	float MaxHealth = 100.0f;

	UFUNCTION()
	void HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
	                  AActor* DamageCauser);

	UFUNCTION()
	void OnRep_Health();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};

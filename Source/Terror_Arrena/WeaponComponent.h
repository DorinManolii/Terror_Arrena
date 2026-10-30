// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponDataAsset.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAmmoChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERROR_ARRENA_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(EditAnywhere, Category="Weapon");
	TObjectPtr<UWeaponDataAsset> WeaponAsset;
	
	UPROPERTY(BlueprintAssignable)
	FOnAmmoChanged OnAmmoChanged;
	
	bool bCanFire = true;
	
	FTimerHandle CanFireTimerHandler;
	
	void Fire();
	
	void CanFire();
	
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,ReplicatedUsing = OnRep_CurrentBullets)
	int32 CurrentBullets = 0;
	
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,ReplicatedUsing = OnRep_ReserveAmmo)
	int32 ReserveAmmo = 0;
	
	UFUNCTION()
	void OnRep_ReserveAmmo();
	
	UFUNCTION()
	void OnRep_CurrentBullets();
	
	void Reload();
	
	void AddBullets(int32 Amount);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

		
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TERROR_ARRENA_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	public:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Weapon")
	float Damage = 10.0f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Weapon")
	float Range = 0.0f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Weapon")
	float FireRate = 0.0f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Weapon")
	bool bFriendlyFire = false;
};


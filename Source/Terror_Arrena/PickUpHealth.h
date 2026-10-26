// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "PickUpHealth.generated.h"

/**
 * 
 */
UCLASS()
class TERROR_ARRENA_API APickUpHealth : public APickUpBase
{
	GENERATED_BODY()
	
	protected:
	virtual bool CanPickUp(AActor* Picker) const override;
	virtual void ApplyPickUp(AActor* Picker) override;
	
	UPROPERTY(EditAnywhere, Category= "PickUp")
	float HealthAmount = 25.f;
	
};

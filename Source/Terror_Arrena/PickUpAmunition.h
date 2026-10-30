// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "PickUpAmunition.generated.h"

/**
 * 
 */
UCLASS()
class TERROR_ARRENA_API APickUpAmunition : public APickUpBase
{
	GENERATED_BODY()
	
	virtual bool CanPickUp(AActor* Picker) const override;
	
	virtual void ApplyPickUp(AActor* Picker) override;
	
	UPROPERTY(EditAnywhere, Category= "PickUp")
	int32 BulletsAmount = 10;
};

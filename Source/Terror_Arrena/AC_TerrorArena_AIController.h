// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WeaponComponent.h"
#include "AC_TerrorArena_AIController.generated.h"

/**
 * 
 */
UCLASS()
class TERROR_ARRENA_API AAC_TerrorArena_AIController : public AAIController
{
	GENERATED_BODY()
	public:
	
	virtual void BeginPlay() override;
	
	FTimerHandle CanFireTimerHandle;
	
	FTimerHandle TimerHandle;
	
	void StartChasing();
	
	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void OnUnPossess() override;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere , Category = "Weapon")
	TObjectPtr<UWeaponComponent> WeaponComponentRef; 
};



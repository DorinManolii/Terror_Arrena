// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
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
	
	void StartChasing();
};



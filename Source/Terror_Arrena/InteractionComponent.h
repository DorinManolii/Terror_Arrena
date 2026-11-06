// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERROR_ARRENA_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();
	
void TryInteract();
	
	UPROPERTY(EditAnywhere,Category = "ADefaultSettings")
	float InteractDistance = 1000.f;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

};
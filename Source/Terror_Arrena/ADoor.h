// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "GameFramework/Actor.h"
#include "ADoor.generated.h"

UCLASS()
class TERROR_ARRENA_API AADoor : public AInteractableBase
{
	GENERATED_BODY()
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:	
	// Sets default values for this actor's properties
	AADoor();
	
	virtual void Interact_Implementation(AActor* Interactor) override;
	
	UPROPERTY(ReplicatedUsing=Rep_IsOpen)
	bool bIsOpen;
	
	UFUNCTION(BLueprintImplementableEvent)
	void OnDoorStateChange(bool bNewState);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
 void Rep_IsOpen();

};

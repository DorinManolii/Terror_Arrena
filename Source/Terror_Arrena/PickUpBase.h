// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpBase.generated.h"

class USphereComponent;

UCLASS(Abstract)
class TERROR_ARRENA_API APickUpBase : public AActor
{
	GENERATED_BODY()
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	// Sets default values for this actor's properties
	APickUpBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CollisionSphere")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	float RespawnTimer = 0.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,ReplicatedUsing= OnRep_IsActive)
	bool bIsHidden = false;
	
	UFUNCTION()
	void OnRep_IsActive();
	
	FTimerHandle OnActorHidden;
	
	bool ShouldBeRespawned = true;

	void SetVisibility();
	
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                     int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual bool CanPickUp(AActor* Picker) const { return true; } ;

	virtual void ApplyPickUp(AActor* Picker) {};
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PickUpBase.generated.h"

UCLASS(Abstract)
class TERROR_ARRENA_API APickUpBase : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	APickUpBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CollisionSphere")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	UStaticMeshComponent* Mesh;

	virtual bool CanPickUp(AActor* Picker) const { return true; } ;

	virtual void ApplyPickUp(AActor* Picker) {};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	float RespawnTimer = 0.f;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                     int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};

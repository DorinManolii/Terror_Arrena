// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpBase.h"

#include "HealthComponent.h"
#include "Terror_ArrenaCharacter.h"


// Sets default values
APickUpBase::APickUpBase()
{
	bReplicates = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(SphereComp);
	SphereComp->SetSphereRadius(25.0f);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));
	Mesh->SetupAttachment(SphereComp);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	
	
	
	
}

// Called when the game starts or when spawned
void APickUpBase::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APickUpBase::OnSphereOverlap);
}


void APickUpBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority()) return;
	if (!CanPickUp(OtherActor))return;
	
	ApplyPickUp(OtherActor);
		Destroy();
}

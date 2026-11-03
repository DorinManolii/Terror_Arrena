// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpBase.h"

#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"


void APickUpBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APickUpBase, bIsHidden);
}

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


void APickUpBase::OnRep_IsActive()
{
	SetActorHiddenInGame(bIsHidden);
	if (bIsHidden)
	{
		SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void APickUpBase::SetVisibility()
{
	if (ShouldBeRespawned)

	{
		GetWorld()->GetTimerManager().ClearTimer(OnActorHidden);
	}

	bIsHidden = false;
	OnRep_IsActive();
}

void APickUpBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	if (!HasAuthority()) return;
	if (!CanPickUp(OtherActor))return;

	ApplyPickUp(OtherActor);
	if (ShouldBeRespawned)
	{
		GetWorld()->GetTimerManager().SetTimer(OnActorHidden, this, &APickUpBase::SetVisibility, RespawnTimer, false);
	
		bIsHidden = true;
		OnRep_IsActive();
	}
	else
	{
		Destroy();
	}
	
}

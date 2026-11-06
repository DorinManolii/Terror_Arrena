// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"

#include "Terror_Arrena.h"
#include "Components/BoxComponent.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("InteractionCollisionBox"));
	SetRootComponent(BoxCollision);
	BoxCollision->SetBoxExtent(FVector(25.0f, 25.0f, 25.0f));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetupAttachment(BoxCollision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionResponseToChannel(ECC_Interaction, ECR_Block);
}


// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractableBase::Interact_Implementation(AActor* Interactor)
{
	if (Interactor == nullptr)return;;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetName());
}

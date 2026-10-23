// Copyright Epic Games, Inc. All Rights Reserved.

#include "Terror_ArrenaPlayerController.h"

#include "EnemiesBaseClass.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Terror_ArrenaCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Terror_Arrena.h"
#include "Terror_ArrenaGameMode.h"
#include "WeaponComponent.h"
#include "Blueprint/UserWidget.h"

void ATerror_ArrenaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (IsLocalPlayerController())
	{
		CreateMainWidget();
	}
}

ATerror_ArrenaPlayerController::ATerror_ArrenaPlayerController()
{
	bIsTouch = false;
	bMoveToMouseCursor = false;

	// create the path following comp
	PathFollowingComponent = CreateDefaultSubobject<UPathFollowingComponent>(TEXT("Path Following Component"));

	// configure the controller
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}


void ATerror_ArrenaPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	OnSpawnPawn.Broadcast(InPawn);
}

void ATerror_ArrenaPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Only set up input on local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			// Setup mouse input events
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this,
			                                   &ATerror_ArrenaPlayerController::OnInputStarted);
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this,
			                                   &ATerror_ArrenaPlayerController::OnSetDestinationTriggered);
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this,
			                                   &ATerror_ArrenaPlayerController::OnSetDestinationReleased);
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this,
			                                   &ATerror_ArrenaPlayerController::OnSetDestinationReleased);
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this,
			                                   &ATerror_ArrenaPlayerController::OnFire);
			EnhancedInputComponent->BindAction(ActionButton, ETriggerEvent::Started, this,
			                                   &ATerror_ArrenaPlayerController::OnActionButton);
			// Setup touch input events
			EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this,
			                                   &ATerror_ArrenaPlayerController::OnInputStarted);
			EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this,
			                                   &ATerror_ArrenaPlayerController::OnTouchTriggered);
			EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this,
			                                   &ATerror_ArrenaPlayerController::OnTouchReleased);
			EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this,
			                                   &ATerror_ArrenaPlayerController::OnTouchReleased);
		}
		else
		{
			UE_LOG(LogTerror_Arrena, Error,
			       TEXT(
				       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
			       ), *GetNameSafe(this));
		}
	}
}

void ATerror_ArrenaPlayerController::OnInputStarted()
{
	StopMovement();

	// Update the move destination to wherever the cursor is pointing at
	UpdateCachedDestination();
}

void ATerror_ArrenaPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// Update the move destination to wherever the cursor is pointing at
	UpdateCachedDestination();

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ATerror_ArrenaPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination,
		                                               FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true,
		                                               true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ATerror_ArrenaPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ATerror_ArrenaPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ATerror_ArrenaPlayerController::UpdateCachedDestination()
{
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility,
		                                         true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
}

void ATerror_ArrenaPlayerController::OnFire()
{
	ServerFire();
}

void ATerror_ArrenaPlayerController::OnActionButton()
{
	ATerror_ArrenaGameMode* MyGM = Cast<ATerror_ArrenaGameMode>(GetWorld()->GetAuthGameMode());

	if (MyGM)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Gm ready"));
		int32 EnemiesAmount = MyGM->Enemies.Num();

		for (int32 i = EnemiesAmount - 1; i >= 0 ; i--)
		{
			AEnemiesBaseClass* Enemy = MyGM->Enemies[i];
			if (Enemy)
			{
				Enemy->Die();
			}
		}
	}
}

void ATerror_ArrenaPlayerController::CreateMainWidget()
{
	UUserWidget* MainWidget = CreateWidget<UUserWidget>(this, MainWidgetClass);

	if (MainWidget)
	{
		MainWidget->AddToViewport();
	}
}

void ATerror_ArrenaPlayerController::ServerFire_Implementation()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		UWeaponComponent* Weapon = ControlledPawn->FindComponentByClass<UWeaponComponent>();
		if (Weapon)
			Weapon->Fire();
	}
}


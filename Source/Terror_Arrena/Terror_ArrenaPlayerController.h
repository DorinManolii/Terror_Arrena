// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
//#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Terror_ArrenaPlayerController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class UPathFollowingComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnPawn,APawn*,PlayerPawn);
/**
 *  Player controller for a top-down perspective game.
 *  Implements point and click based controls
 */
UCLASS(abstract)
class ATerror_ArrenaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
protected:

	/** Component used for moving along a NavMesh path. */
	UPROPERTY(VisibleDefaultsOnly, Category = AI)
	TObjectPtr<UPathFollowingComponent> PathFollowingComponent;

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, Category="Input")
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UNiagaraSystem> FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> SetDestinationTouchAction;
	
	//Fire Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> FireAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> ActionButton;
	
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	/** Set to true if we're using touch input */
	uint32 bIsTouch : 1;

	/** Saved location of the character movement destination */
	FVector CachedDestination;

	/** Time that the click input has been pressed */
	float FollowTime = 0.0f;
	

	
public:

	/** Constructor */
	ATerror_ArrenaPlayerController();
	
	UPROPERTY(BlueprintAssignable)
	FOnSpawnPawn OnSpawnPawn;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite);
	TSubclassOf<UUserWidget> MainWidgetClass;
	
	void CreateMainWidget();
	
	UFUNCTION(Server, Reliable)
	void ServerFire();
	
	virtual void SetPawn(APawn* InPawn) override;
protected:

	/** Initialize input bindings */
	virtual void SetupInputComponent() override;
	
	/** Input handlers */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();
	void OnFire();
	void OnActionButton();

	/** Helper function to get the move destination */
	void UpdateCachedDestination();
};



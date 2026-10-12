// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Terror_ArrenaGameMode.generated.h"

/**
 *  Simple Game Mode for a top-down perspective game
 *  Sets the default gameplay framework classes
 *  Check the Blueprint derived class for the set values
 */
UCLASS(abstract)
class ATerror_ArrenaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	/** Constructor */
	ATerror_ArrenaGameMode();
};




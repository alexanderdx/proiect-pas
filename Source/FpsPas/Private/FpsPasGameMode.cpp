// Copyright Epic Games, Inc. All Rights Reserved.

#include "FpsPasGameMode.h"

#include "FpsPasPlayerController.h"
#include "UObject/ConstructorHelpers.h"


AFpsPasGameMode::AFpsPasGameMode() : Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter")
	);
	
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

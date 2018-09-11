// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "VRSGameMode.h"
#include "VRSHUD.h"
#include "VRSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVRSGameMode::AVRSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AVRSHUD::StaticClass();
}

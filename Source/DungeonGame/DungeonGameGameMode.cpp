// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonGameGameMode.h"
#include "DungeonGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADungeonGameGameMode::ADungeonGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_DungeonGameCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

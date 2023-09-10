// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoMand_KnightGameMode.h"
#include "NoMand_KnightCharacter.h"

ANoMand_KnightGameMode::ANoMand_KnightGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ANoMand_KnightCharacter::StaticClass();	
}

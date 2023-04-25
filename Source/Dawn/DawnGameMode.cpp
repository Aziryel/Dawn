// Copyright Epic Games, Inc. All Rights Reserved.

#include "DawnGameMode.h"
#include "DawnCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADawnGameMode::ADawnGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

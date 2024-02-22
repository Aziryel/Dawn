// Copyright Aziryel


#include "GameModes/DGameModeBase.h"

UCharacterClassInfo* ADGameModeBase::GetCharacterClassInfo() const
{
	return CharacterClassInfo.Get();
}

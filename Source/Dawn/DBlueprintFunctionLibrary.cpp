// Copyright Aziryel


#include "DBlueprintFunctionLibrary.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

void UDBlueprintFunctionLibrary::ClearTargetData(FGameplayAbilityTargetDataHandle& TargetData)
{
	TargetData.Clear();
}

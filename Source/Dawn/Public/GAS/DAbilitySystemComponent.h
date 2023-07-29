// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class DAWN_API UDAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	// Exposes GetTagCount to Blueprint
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Abilities", Meta = (DisplayName = "GetTagCount", ScriptName = "GetTagCount"))
	int32 K2_GetTagCount(FGameplayTag TagToCheck) const;
	
};

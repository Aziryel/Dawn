// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Dawn/Dawn.h"
#include "DGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class DAWN_API UDGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UDGameplayAbility();

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	EDAbilityInputID AbilityInputID = EDAbilityInputID::None;

	// Value associated with an ability without trying to automatically activate the input
	// Passive abilities won't be tied to input so we need a generic way to associate abilities with slots
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	EDAbilityInputID AbilityID = EDAbilityInputID::None;
};

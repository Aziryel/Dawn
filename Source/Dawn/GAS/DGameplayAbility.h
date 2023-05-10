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

	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilites forced on others.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool bActivateAbilityOnGranted;

	// If an ability is marked as 'ActivateAbilityOnGranted', activate them immediately when given here
	// Epic's comment: Projects may want to initiate passives or do other "BeginPlay" type of logic here.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	// Is the player's input currently pressed? Only works if the ability is bound to input.
	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual bool IsInputPressed() const;
	
};

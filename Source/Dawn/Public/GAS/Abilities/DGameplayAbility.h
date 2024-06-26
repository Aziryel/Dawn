// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DGameplayAbility.generated.h"

class ADPlayerState;
/**
 * 
 */
UCLASS()
class DAWN_API UDGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UDGameplayAbility();

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (Categories = "InputTag"))
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat Damage;

	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilities forced on others.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool bActivateAbilityOnGranted;

	// If an ability is marked as 'ActivateAbilityOnGranted', activate them immediately when given here
	// Epic's comment: Projects may want to initiate passives or do other "BeginPlay" type of logic here.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	// Is the player's input currently pressed? Only works if the ability is bound to input.
	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual bool IsInputPressed() const;

	UPROPERTY(BlueprintReadOnly)
	ADPlayerState* OwningPlayerState;
	
};

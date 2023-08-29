// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/DGameplayAbility.h"
#include "DProjectileSpell.generated.h"

class ADProjectile;
/**
 * 
 */
UCLASS()
class DAWN_API UDProjectileSpell : public UDGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ADProjectile> ProjectileClass;
};

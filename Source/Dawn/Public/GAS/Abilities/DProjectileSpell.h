// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/DGameplayAbility.h"
#include "DProjectileSpell.generated.h"

class ADProjectile;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class DAWN_API UDProjectileSpell : public UDGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetProjectileHitResult();

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ADProjectile> ProjectileClass;

	UPROPERTY(BlueprintReadWrite)
	FHitResult ProjectileHitResult;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

};

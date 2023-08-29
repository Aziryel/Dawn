// Copyright Aziryel


#include "GAS/Abilities/DProjectileSpell.h"

#include "Actor/DProjectile.h"
#include "Interfaces/CombatInterface.h"

void UDProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation =CombatInterface->GetCombatSocketLocation();
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		//TODO: Set the projectile rotation.
		
		ADProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: Give the projectile a Gameplay Effect Spec for causing damage.
		
		Projectile->FinishSpawning(SpawnTransform);
	}

}

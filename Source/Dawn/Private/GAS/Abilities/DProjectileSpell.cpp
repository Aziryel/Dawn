// Copyright Aziryel


#include "GAS/Abilities/DProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Actor/DProjectile.h"
#include "Character/DPlayerCharacter.h"
#include "Interfaces/CombatInterface.h"
#include "PlayerState/DPlayerState.h"

void UDProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UDProjectileSpell::SetProjectileHitResult()
{
	ADPlayerCharacter* PlayerCharacter = Cast<ADPlayerCharacter>(GetAvatarActorFromActorInfo());
	if (PlayerCharacter)
	{
		OwningPlayerState = Cast<ADPlayerState>(PlayerCharacter->GetPlayerState());
		if (OwningPlayerState)
		{
			ProjectileHitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(OwningPlayerState->CurrentTracedTarget, 0);
			if (!ProjectileHitResult.GetActor())
			{
				ProjectileHitResult.Location = PlayerCharacter->GetActorForwardVector();
			}
		}
	}
}

void UDProjectileSpell::SpawnProjectile()
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		FTransform ProjectileSpawnTransform;
		ProjectileSpawnTransform.SetLocation(SocketLocation);
		
		if (ProjectileHitResult.IsValidBlockingHit())
		{
			FRotator Rotation = (ProjectileHitResult.GetActor()->GetActorLocation() - SocketLocation).Rotation();
			ProjectileSpawnTransform.SetRotation(Rotation.Quaternion());
		}
		else
		{
			ProjectileSpawnTransform.SetRotation(GetAvatarActorFromActorInfo()->GetActorForwardVector().Rotation().Quaternion());
		}
		
		ADProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADProjectile>(
			ProjectileClass,
			ProjectileSpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: Give the projectile a Gameplay Effect Spec for causing damage.
		Projectile->FinishSpawning(ProjectileSpawnTransform);
	}
}

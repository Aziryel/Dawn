// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/DGameplayAbility.h"
#include "AbilitySystemComponent.h"

UDGameplayAbility::UDGameplayAbility()
{
	bActivateAbilityOnGranted = false;
}

void UDGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

bool UDGameplayAbility::IsInputPressed() const
{
	FGameplayAbilitySpec* Spec = GetCurrentAbilitySpec();
	return Spec && Spec->InputPressed;
}

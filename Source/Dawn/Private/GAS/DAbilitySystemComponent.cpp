// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/DAbilitySystemComponent.h"

#include "DGameplayTags.h"

void UDAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UDAbilitySystemComponent::EffectApplied);
	
}

void UDAbilitySystemComponent::EffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	
	EffectAssetTags.Broadcast(TagContainer);
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerState/DPlayerState.h"
#include "GAS/DAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

ADPlayerState::ADPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UDAttributeSet>(TEXT("AttributeSet"));
	
	NetUpdateFrequency = 100.f;
}

void ADPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADPlayerState, Level);
}

UAbilitySystemComponent* ADPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UDAttributeSet* ADPlayerState::GetAttributeSetBase() const
{
	return AttributeSet;
}

void ADPlayerState::OnRep_Level(int32 OldLevel)
{
	
}

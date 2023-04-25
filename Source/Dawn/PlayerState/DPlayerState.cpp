// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerState.h"

ADPlayerState::ADPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UDAttributeSet>(TEXT("AttributeSet"));
}

void ADPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ADPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ADPlayerState::MaxHealthChanged);
		ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaAttribute()).AddUObject(this, &ADPlayerState::ManaChanged);
		MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxManaAttribute()).AddUObject(this, &ADPlayerState::MaxManaChanged);
		StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaAttribute()).AddUObject(this, &ADPlayerState::StaminaChanged);
		MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &ADPlayerState::MaxStaminaChanged);
		ComboCounterChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetComboCounterAttribute()).AddUObject(this, &ADPlayerState::ComboCounterChanged);
		StrengthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStrengthAttribute()).AddUObject(this, &ADPlayerState::StrengthChanged);
		DexterityChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetDexterityAttribute()).AddUObject(this, &ADPlayerState::DexterityChanged);
		VitalityChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetVitalityAttribute()).AddUObject(this, &ADPlayerState::VitalityChanged);
		IntelligenceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetIntelligenceAttribute()).AddUObject(this, &ADPlayerState::IntelligenceChanged);
		WisdomChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetWisdomAttribute()).AddUObject(this, &ADPlayerState::WisdomChanged);
		DevotionChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetDevotionAttribute()).AddUObject(this, &ADPlayerState::DevotionChanged);
		BlasphemyChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetBlasphemyAttribute()).AddUObject(this, &ADPlayerState::BlasphemyChanged);
		DraconiumChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetDraconiumAttribute()).AddUObject(this, &ADPlayerState::DraconiumChanged);
		TimeShardsChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetTimeShardsAttribute()).AddUObject(this, &ADPlayerState::TimeShardsChanged);
		AncientTimeShardsChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetAncientTimeShardsAttribute()).AddUObject(this, &ADPlayerState::AncientTimeShardsChanged);
	}
}

UAbilitySystemComponent* ADPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UDAttributeSet* ADPlayerState::GetAttributeSetBase() const
{
	return AttributeSet;
}

void ADPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::ManaChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::MaxManaChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::StaminaChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::ComboCounterChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::StrengthChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::DexterityChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::VitalityChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::IntelligenceChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::WisdomChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::DevotionChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::BlasphemyChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::DraconiumChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::TimeShardsChanged(const FOnAttributeChangeData& Data)
{
}

void ADPlayerState::AncientTimeShardsChanged(const FOnAttributeChangeData& Data)
{
}

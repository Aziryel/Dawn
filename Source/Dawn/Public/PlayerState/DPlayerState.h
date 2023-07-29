// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GAS/DAbilitySystemComponent.h"
#include "GAS/DAttributeSet.h"
#include "GameFramework/PlayerState.h"
#include "DPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DAWN_API ADPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ADPlayerState();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UDAttributeSet* GetAttributeSetBase() const;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle ManaChangedDelegateHandle;
	FDelegateHandle MaxManaChangedDelegateHandle;
	FDelegateHandle StaminaChangedDelegateHandle;
	FDelegateHandle MaxStaminaChangedDelegateHandle;
	FDelegateHandle ComboCounterChangedDelegateHandle;
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void ManaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxManaChanged(const FOnAttributeChangeData& Data);
	virtual void StaminaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void ComboCounterChanged(const FOnAttributeChangeData& Data);

	FDelegateHandle StrengthChangedDelegateHandle;
	FDelegateHandle DexterityChangedDelegateHandle;
	FDelegateHandle VitalityChangedDelegateHandle;
	FDelegateHandle IntelligenceChangedDelegateHandle;
	FDelegateHandle WisdomChangedDelegateHandle;
	FDelegateHandle DevotionChangedDelegateHandle;
	FDelegateHandle BlasphemyChangedDelegateHandle;
	virtual void StrengthChanged(const FOnAttributeChangeData& Data);
	virtual void DexterityChanged(const FOnAttributeChangeData& Data);
	virtual void VitalityChanged(const FOnAttributeChangeData& Data);
	virtual void IntelligenceChanged(const FOnAttributeChangeData& Data);
	virtual void WisdomChanged(const FOnAttributeChangeData& Data);
	virtual void DevotionChanged(const FOnAttributeChangeData& Data);
	virtual void BlasphemyChanged(const FOnAttributeChangeData& Data);
	
	FDelegateHandle DraconiumChangedDelegateHandle;
	FDelegateHandle TimeShardsChangedDelegateHandle;
	FDelegateHandle AncientTimeShardsChangedDelegateHandle;
	virtual void DraconiumChanged(const FOnAttributeChangeData& Data);
	virtual void TimeShardsChanged(const FOnAttributeChangeData& Data);
	virtual void AncientTimeShardsChanged(const FOnAttributeChangeData& Data);

	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Ability System Component")
	TObjectPtr<UDAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Ability System Component")
	TObjectPtr<UDAttributeSet> AttributeSet;
};

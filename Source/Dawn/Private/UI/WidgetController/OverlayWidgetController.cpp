// Copyright Aziryel


#include "UI/WidgetController/OverlayWidgetController.h"

#include "GAS/DAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UDAttributeSet* DAttributeSet = CastChecked<UDAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(DAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(DAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(DAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(DAttributeSet->GetMaxMana());
	OnStaminaChanged.Broadcast(DAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(DAttributeSet->GetMaxStamina());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UDAttributeSet* DAttributeSet = CastChecked<UDAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		DAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		DAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		DAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		DAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		DAttributeSet->GetStaminaAttribute()).AddUObject(this, &UOverlayWidgetController::StaminaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		DAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxStaminaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const 
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const 
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::StaminaChanged(const FOnAttributeChangeData& Data) const
{
	
	OnStaminaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxStaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxStaminaChanged.Broadcast(Data.NewValue);
}

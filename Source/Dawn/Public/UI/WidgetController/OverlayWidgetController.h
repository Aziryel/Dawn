// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/DWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChangedSignature, float, NewStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxStaminaChangedSignature, float, NewMaxStamina);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DAWN_API UOverlayWidgetController : public UDWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnStaminaChangedSignature OnStaminaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxStaminaChangedSignature OnMaxStaminaChanged;

	virtual void HealthChanged(const FOnAttributeChangeData& Data) const;
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	virtual void ManaChanged(const FOnAttributeChangeData& Data) const;
	virtual void MaxManaChanged(const FOnAttributeChangeData& Data) const;
	virtual void StaminaChanged(const FOnAttributeChangeData& Data) const;
	virtual void MaxStaminaChanged(const FOnAttributeChangeData& Data) const;
	
};

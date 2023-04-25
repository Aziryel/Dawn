// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "DInputConfig.h"
#include "GameplayTagContainer.h"
#include "DEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class DAWN_API UDEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserClass, typename FuncType>
	void BindActionByTag(const UDInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);
};

template <class UserClass, typename FuncType>
void UDEnhancedInputComponent::BindActionByTag(const UDInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	check(InputConfig)
	if (const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}


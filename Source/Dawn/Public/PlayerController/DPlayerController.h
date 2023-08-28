// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/DPlayerStatsWidget.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

struct FGameplayTag;
class UInputMappingContext;
class UDInputConfig;
class ADPlayerState;
struct FInputActionValue;
class UDAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class DAWN_API ADPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRateGamepad;

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
	/** Handles moving forward/backward */
	void Input_Move(const FInputActionValue& InputActionValue);
	/** Handles mouse and stick look */
	void Input_Look(const FInputActionValue& InputActionValue);
	/** Handles Jumping */
	void Input_Jump(const FInputActionValue& InputActionValue);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> KeyboardMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> GamepadMappingContext;
	
	/** The input config that maps Input Actions to Input Tags */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UDInputConfig> InputConfig;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY()
	TObjectPtr<UDAbilitySystemComponent> DAbilitySystemComponent;

	UDAbilitySystemComponent* GetASC();
};

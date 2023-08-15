// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dawn/Dawn.h"
#include "UI/Widget/DPlayerStatsWidget.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPrimaryAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSecondaryAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponArtAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbility1Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbility2Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbility3Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbility4Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbility5Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbility6Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbility7Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPauseAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractAction);

class UInputMappingContext;
class UDInputConfig;
class ADPlayerState;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class DAWN_API ADPlayerController : public APlayerController
{
	GENERATED_BODY()

	ADPlayerController();
	virtual void OnRep_PlayerState() override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UIWidgets")
	TSubclassOf<UDPlayerStatsWidget> UIPlayerStatsClass;
	UPROPERTY(BlueprintReadWrite, Category = "UI Widgets")
	UDPlayerStatsWidget* UIPlayerStats;

	UFUNCTION()
	void TogglePlayerStats();

	UFUNCTION()
	void CreateHUD();

	/** The input config that maps Input Actions to Input Tags */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UDInputConfig* InputConfig;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void SendLocalInputToASC(bool bIsPressed, const EDAbilityInputID AbilityInputID);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRateGamepad;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Action Inputs")
	FOnPrimaryAction OnPrimaryAction;
	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Action Inputs")
	FOnSecondaryAction OnSecondaryAction;
	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Action Inputs")
	FOnWeaponArtAction OnWeaponArtAction;
	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Action Inputs")
	FOnAbility1Action OnAbility1Action;
	UPROPERTY(BlueprintAssignable, Category = "Action Inputs")
	FOnAbility2Action OnAbility2Action;
	UPROPERTY(BlueprintAssignable, Category = "Action Inputs")
	FOnAbility3Action OnAbility3Action;
	UPROPERTY(BlueprintAssignable, Category = "Action Inputs")
	FOnAbility4Action OnAbility4Action;
	UPROPERTY(BlueprintAssignable, Category = "Action Inputs")
	FOnAbility5Action OnAbility5Action;
	UPROPERTY(BlueprintAssignable, Category = "Action Inputs")
	FOnAbility6Action OnAbility6Action;
	UPROPERTY(BlueprintAssignable, Category = "Action Inputs")
	FOnAbility7Action OnAbility7Action;
	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Action Inputs")
	FOnPauseAction OnPauseAction;
	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Action Inputs")
	FOnInteractAction OnInteractAction;

	/** Activates Primary Action. */
	void OnPrimaryActionUse();
	/** Activates Secondary Action. */
	void OnSecondaryActionUse();
	/** Activates Primary Action. */
	void OnWeaponArtUse();
	/** Activates Secondary Action. */
	void OnAbility1ActionUse();
	/** Activates Secondary Action. */
	void OnAbility2ActionUse();
	/** Activates Secondary Action. */
	void OnAbility3ActionUse();
	/** Activates Secondary Action. */
	void OnAbility4ActionUse();
	/** Activates Secondary Action. */
	void OnAbility5ActionUse();
	/** Activates Secondary Action. */
	void OnAbility6ActionUse();
	/** Activates Secondary Action. */
	void OnAbility7ActionUse();
	/** Activates the Pause action. */
	void OnPauseActionUse();
	/** Activates the Pause action. */
	void OnInteractActionUse();

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
	/** Handles the Primary Action */
	void Input_Primary(const FInputActionValue& InputActionValue);
	/** Handles the Secondary Action */
	void Input_Secondary(const FInputActionValue& InputActionValue);
	/** Handles the WeaponArt Action */
	void Input_WeaponArt(const FInputActionValue& InputActionValue);
	/** Handles the Ability1 Action */
	void Input_Ability1(const FInputActionValue& InputActionValue);
	/** Handles the Ability2 Action */
	void Input_Ability2(const FInputActionValue& InputActionValue);
	/** Handles the Ability3 Action */
	void Input_Ability3(const FInputActionValue& InputActionValue);
	/** Handles the Ability4 Action */
	void Input_Ability4(const FInputActionValue& InputActionValue);
	/** Handles the Ability5 Action */
	void Input_Ability5(const FInputActionValue& InputActionValue);
	/** Handles the Ability6 Action */
	void Input_Ability6(const FInputActionValue& InputActionValue);
	/** Handles the Ability7 Action */
	void Input_Ability7(const FInputActionValue& InputActionValue);
	/** Handle the Pause action */
	void Input_Pause(const FInputActionValue& InputActionValue);
	/** Handle the Pause action */
	void Input_Interact(const FInputActionValue& InputActionValue);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> KeyboardMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> GamepadMappingContext;

	UPROPERTY()
	ADPlayerState* DPlayerState;
};

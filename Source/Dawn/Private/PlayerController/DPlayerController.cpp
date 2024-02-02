// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerController/DPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DGameplayTags.h"
#include "GameplayTagContainer.h"
#include "EnhancedInputSubsystems.h"
#include "Character/DPlayerCharacter.h"
#include "Input/DEnhancedInputComponent.h"


ADPlayerController::ADPlayerController()
{
	bReplicates = true;

	TurnRateGamepad = 10.f;
}

void ADPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* EISubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!EISubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid EISubsystem in the DPlayerController Class"));
	}	

	if (EISubsystem && KeyboardMappingContext && GamepadMappingContext)
	{
		EISubsystem->AddMappingContext(KeyboardMappingContext, 0);
		EISubsystem->AddMappingContext(GamepadMappingContext, 0);
	}
}

void ADPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/*
	 * InputComponent points directly to a DEnhancedInputComponent Class (Custom Class) because we specified that in the
	 * Project Settings -> Input -> Default Classes -> Default Input Component Class
	 */
	UDEnhancedInputComponent* DEnhancedInputComponent = CastChecked<UDEnhancedInputComponent>(InputComponent);

	const FDGameplayTags& GameplayTags = FDGameplayTags::Get();

	DEnhancedInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
	
	//TODO: Change this for the new system
	DEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Move);
	DEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Look);
	DEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Look);
	DEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Jump, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Jump);
	if (GetASC())
	{
		DEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_ConfirmTargeting, ETriggerEvent::Triggered, GetASC(), &UAbilitySystemComponent::LocalInputConfirm);
		DEnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_CancelTargeting, ETriggerEvent::Triggered, GetASC(), &UAbilitySystemComponent::LocalInputCancel);
	}
	
}

void ADPlayerController::TurnAtRate(float Rate)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
	}
}

void ADPlayerController::LookUpAtRate(float Rate)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
	}
}

void ADPlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(MovementRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(MovementRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ADPlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookValue = InputActionValue.Get<FVector2D>();

	if (LookValue.X != 0.0f)
	{
		TurnAtRate(LookValue.X);
	}

	if (LookValue.Y != 0.0f)
	{
		LookUpAtRate(LookValue.Y);
	}
}

void ADPlayerController::Input_Jump(const FInputActionValue& InputActionValue)
{
	ADPlayerCharacter* PlayerCharacter = CastChecked<ADPlayerCharacter>(GetCharacter());
	PlayerCharacter->Jump();
}

void ADPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void ADPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void ADPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

UDAbilitySystemComponent* ADPlayerController::GetASC()
{
	if (DAbilitySystemComponent == nullptr)
	{
		DAbilitySystemComponent = Cast<UDAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return DAbilitySystemComponent;
}



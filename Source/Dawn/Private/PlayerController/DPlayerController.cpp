// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerController/DPlayerController.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Character/DPlayerCharacter.h"
#include "Dawn/Dawn.h"
#include "Dawn/DGameplayTags.h"
#include "GAS/DAttributeSet.h"
#include "Input/DEnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerState/DPlayerState.h"
#include "UI/DPlayerStatsWidget.h"


ADPlayerController::ADPlayerController()
{
	bReplicates = true;

	TurnRateGamepad = 45.f;
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
	UDEnhancedInputComponent* EnhancedInputComponent = CastChecked<UDEnhancedInputComponent>(InputComponent);

	const FDGameplayTags& GameplayTags = FDGameplayTags::Get();

	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Move);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Look);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Look);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Primary, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Primary);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Secondary, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Secondary);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability1, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Ability1);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability2, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Ability2);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability3, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Ability3);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability4, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Ability4);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability5, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Ability5);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability6, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Ability6);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability7, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Ability7);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Jump, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Jump);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Pause, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Pause);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Interact, ETriggerEvent::Triggered, this, &ADPlayerController::Input_Interact);
	
}

void ADPlayerController::SendLocalInputToASC(bool bIsPressed, const EDAbilityInputID AbilityInputID)
{
	if (!DPlayerState)
	{
		DPlayerState = GetPlayerState<ADPlayerState>();
	}
	if (DPlayerState && DPlayerState->GetAbilitySystemComponent())
	{
		if (bIsPressed)
		{
			UKismetSystemLibrary::PrintString(this, "We are pressing our input");
			DPlayerState->GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<int32>(AbilityInputID));
		}
		else
		{
			UKismetSystemLibrary::PrintString(this, "We are releasing our input");
			DPlayerState->GetAbilitySystemComponent()->AbilityLocalInputReleased(static_cast<int32>(AbilityInputID));
		}
	}
	
}

void ADPlayerController::OnPrimaryActionUse()
{
	OnPrimaryAction.Broadcast();
}

void ADPlayerController::OnSecondaryActionUse()
{
	OnSecondaryAction.Broadcast();
}

void ADPlayerController::OnWeaponArtUse()
{
	OnWeaponArtAction.Broadcast();
}

void ADPlayerController::OnAbility1ActionUse()
{
	OnAbility1Action.Broadcast();
}

void ADPlayerController::OnAbility2ActionUse()
{
	OnAbility2Action.Broadcast();
}

void ADPlayerController::OnAbility3ActionUse()
{
	OnAbility3Action.Broadcast();
}

void ADPlayerController::OnAbility4ActionUse()
{
	OnAbility4Action.Broadcast();
}

void ADPlayerController::OnAbility5ActionUse()
{
	OnAbility5Action.Broadcast();
}

void ADPlayerController::OnAbility6ActionUse()
{
	OnAbility6Action.Broadcast();
}

void ADPlayerController::OnAbility7ActionUse()
{
	OnAbility7Action.Broadcast();
}

void ADPlayerController::OnPauseActionUse()
{
	OnPauseAction.Broadcast();
}

void ADPlayerController::OnInteractActionUse()
{
	OnInteractAction.Broadcast();
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

void ADPlayerController::Input_Primary(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::PrimaryAbility);
	OnPrimaryActionUse();
}

void ADPlayerController::Input_Secondary(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::SecondaryAbility);
	OnSecondaryActionUse();
}

void ADPlayerController::Input_WeaponArt(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::WeaponArt);
	OnWeaponArtUse();
}

void ADPlayerController::Input_Ability1(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability1);
	OnAbility1ActionUse();
}

void ADPlayerController::Input_Ability2(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability2);
	OnAbility2ActionUse();
}

void ADPlayerController::Input_Ability3(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability3);
	OnAbility3ActionUse();
}

void ADPlayerController::Input_Ability4(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability4);
	OnAbility4ActionUse();
}

void ADPlayerController::Input_Ability5(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability5);
	OnAbility5ActionUse();
}

void ADPlayerController::Input_Ability6(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability6);
	OnAbility6ActionUse();
}

void ADPlayerController::Input_Ability7(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability7);
	OnAbility7ActionUse();
}

void ADPlayerController::Input_Pause(const FInputActionValue& InputActionValue)
{
	TogglePlayerStats();
	OnPauseActionUse();
}

void ADPlayerController::Input_Interact(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Interact);
	OnInteractActionUse();
}

void ADPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	CreateHUD();
}

void ADPlayerController::TogglePlayerStats()
{
	/*if (!UIPlayerStats || UIPlayerStats->GetName() == "None")
	{
		UIPlayerStats = CreateWidget<UDPlayerStatsWidget>(this, UIPlayerStatsClass);
		UIPlayerStats->AddToViewport();
		UIPlayerStats->SetVisibility(ESlateVisibility::Collapsed);
		UE_LOG(LogTemp, Warning, TEXT("Create Widget!"));
	}*/
	if (UIPlayerStats->StatsBorder && UIPlayerStats->StatsBorder->GetVisibility() == ESlateVisibility::Collapsed)
	{
		UIPlayerStats->StatsBorder->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(this, UIPlayerStats);
		SetShowMouseCursor(true);
		SetIgnoreLookInput(true);
		SetIgnoreMoveInput(true);
		UIPlayerStats->SetFocus();
	}
	else
	{
		UIPlayerStats->StatsBorder->SetVisibility(ESlateVisibility::Collapsed);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
		SetShowMouseCursor(false);
		SetIgnoreLookInput(false);
		SetIgnoreMoveInput(false);
	}
}

void ADPlayerController::CreateHUD()
{
	if (!IsLocalPlayerController())
	{
		return;
	}

	ADPlayerState* PS = GetPlayerState<ADPlayerState>();
	if (!PS)
	{
		return;
	}
	
	if (!UIPlayerStats || UIPlayerStats->GetName() == "None")
	{
		UIPlayerStats = CreateWidget<UDPlayerStatsWidget>(this, UIPlayerStatsClass);
		UIPlayerStats->AddToViewport();
		UIPlayerStats->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		UIPlayerStats->UpdateText(UIPlayerStats->HealthText, PS->GetAttributeSetBase()->GetHealth());
		UIPlayerStats->UpdateProgressBar(UIPlayerStats->HealthBar, PS->GetAttributeSetBase()->GetHealth(), PS->GetAttributeSetBase()->GetMaxHealth());
		UIPlayerStats->UpdateText(UIPlayerStats->ManaText, PS->GetAttributeSetBase()->GetMana());
		UIPlayerStats->UpdateProgressBar(UIPlayerStats->ManaBar, PS->GetAttributeSetBase()->GetMana(), PS->GetAttributeSetBase()->GetMaxMana());
		// Update Stats
		UIPlayerStats->UpdateStats(UIPlayerStats->StrText, PS->GetAttributeSetBase()->GetStrength());
		UIPlayerStats->UpdateStats(UIPlayerStats->DexText, PS->GetAttributeSetBase()->GetDexterity());
		UIPlayerStats->UpdateStats(UIPlayerStats->VitText, PS->GetAttributeSetBase()->GetVitality());
		UIPlayerStats->UpdateStats(UIPlayerStats->IntText, PS->GetAttributeSetBase()->GetIntelligence());
		UIPlayerStats->UpdateStats(UIPlayerStats->WisText, PS->GetAttributeSetBase()->GetWisdom());
		UE_LOG(LogTemp, Warning, TEXT("Create Widget!"));
	}
}



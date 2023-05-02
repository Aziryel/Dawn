// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerCharacter.h"

#include "DCharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Dawn/DGameplayTags.h"
#include "Dawn/Components/DCombatComponent.h"
#include "Dawn/Input/DEnhancedInputComponent.h"
#include "Dawn/PlayerController/DPlayerController.h"
#include "Dawn/PlayerState/DPlayerState.h"
#include "Dawn/Weapon/DWeaponBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

ADPlayerCharacter::ADPlayerCharacter(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->MaxCustomMovementSpeed = 500.f;
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	TurnRateGamepad = 45.f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	CombatComponent = CreateDefaultSubobject<UDCombatComponent>("CombatComponent");
	CombatComponent->SetIsReplicated(true);
}

void ADPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME_CONDITION_NOTIFY(ADPlayerCharacter,bInputDisabled,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION(ADPlayerCharacter, OverlappingWeapon, COND_OwnerOnly);
}

void ADPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		if (UEnhancedInputLocalPlayerSubsystem* EISubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			EISubsystem->AddMappingContext(KeyboardMappingContext, 0);
			EISubsystem->AddMappingContext(GamepadMappingContext, 0);
		}
	}
	
}

void ADPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// This is for the Server, the same settings are set on OnRep_PlayerState for Clients in the DPlayerCharacter class
	ADPlayerState* PS = GetPlayerState<ADPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UDAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
		AddCharacterAbilities(CharacterAbilities);
		Attributes = PS->GetAttributeSetBase();
		InitializeAttributes();

		SetHealth(Attributes->GetMaxHealth());
		SetMana(Attributes->GetMaxMana());
		SetStamina(Attributes->GetMaxStamina());
	}

	ADPlayerController* PC = Cast<ADPlayerController>(GetController());
	if (PC)
	{
		PC->CreateHUD();
	}
}

// Called to bind functionality to input
void ADPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	UDEnhancedInputComponent* EnhancedInputComponent = Cast<UDEnhancedInputComponent>(PlayerInputComponent);

	//Make sure to set your input component class in the InputSettings->DefaultClasses
	check(EnhancedInputComponent);
	
	const FDGameplayTags& GameplayTags = FDGameplayTags::Get();

	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Move);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Look);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Look);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Primary, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Primary);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Secondary, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Secondary);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability1, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Ability1);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability2, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Ability2);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability3, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Ability3);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability4, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Ability4);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability5, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Ability5);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability6, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Ability6);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Ability7, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Ability7);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Jump, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Jump);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Pause, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Pause);
	EnhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.InputTag_Interact, ETriggerEvent::Triggered, this, &ADPlayerCharacter::Input_Interact);
}

void ADPlayerCharacter::SendLocalInputToASC(bool bIsPressed, const EDAbilityInputID AbilityInputID)
{
	if (!AbilitySystemComponent)
	{
		UKismetSystemLibrary::PrintString(this, "We don't have a valid ASC"); return;
	}

	if (bIsPressed)
	{
		UKismetSystemLibrary::PrintString(this, "We are pressing our input");
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(AbilityInputID));
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, "We are releasing our input");
		AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(AbilityInputID));
	}
}

void ADPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		if (UEnhancedInputLocalPlayerSubsystem* EISubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			EISubsystem->AddMappingContext(KeyboardMappingContext, 0);
			EISubsystem->AddMappingContext(GamepadMappingContext, 0);
		}
	}
	
	ADPlayerState* PS = GetPlayerState<ADPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UDAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
		AddCharacterAbilities(CharacterAbilities);
		Attributes = PS->GetAttributeSetBase();
		InitializeAttributes();

		SetHealth(Attributes->GetMaxHealth());
		SetMana(Attributes->GetMaxMana());
		SetStamina(Attributes->GetMaxStamina());
	}
}

void ADPlayerCharacter::OnPrimaryActionUse()
{
	OnPrimaryAction.Broadcast();
}

void ADPlayerCharacter::OnSecondaryActionUse()
{
	OnSecondaryAction.Broadcast();
}

void ADPlayerCharacter::OnWeaponArtUse()
{
	OnWeaponArtAction.Broadcast();
}

void ADPlayerCharacter::OnAbility1ActionUse()
{
	OnAbility1Action.Broadcast();
}

void ADPlayerCharacter::OnAbility2ActionUse()
{
	OnAbility2Action.Broadcast();
}

void ADPlayerCharacter::OnAbility3ActionUse()
{
	OnAbility3Action.Broadcast();
}

void ADPlayerCharacter::OnAbility4ActionUse()
{
	OnAbility4Action.Broadcast();
}

void ADPlayerCharacter::OnAbility5ActionUse()
{
	OnAbility5Action.Broadcast();
}

void ADPlayerCharacter::OnAbility6ActionUse()
{
	OnAbility6Action.Broadcast();
}

void ADPlayerCharacter::OnAbility7ActionUse()
{
	OnAbility7Action.Broadcast();
}

void ADPlayerCharacter::OnInteractActionUse()
{
	OnInteractAction.Broadcast();
}

void ADPlayerCharacter::OnPauseActionUse()
{
	OnPauseAction.Broadcast();
}

void ADPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	if (Controller != nullptr)
	{
		const FVector2D MoveValue = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (MoveValue.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			AddMovementInput(MovementDirection, MoveValue.X);
		}

		if (MoveValue.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(MovementDirection, MoveValue.Y);
		}
	}
}

void ADPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	if (Controller != nullptr)
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
}

void ADPlayerCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	Jump();
}

void ADPlayerCharacter::Input_Primary(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::PrimaryAbility);
	OnPrimaryActionUse();
}

void ADPlayerCharacter::Input_Secondary(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::SecondaryAbility);
	OnSecondaryActionUse();
}

void ADPlayerCharacter::Input_WeaponArt(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::WeaponArt);
	OnWeaponArtUse();
}

void ADPlayerCharacter::Input_Ability1(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability1);
	OnAbility1ActionUse();
}

void ADPlayerCharacter::Input_Ability2(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability2);
	OnAbility2ActionUse();
}

void ADPlayerCharacter::Input_Ability3(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability3);
	OnAbility3ActionUse();
}

void ADPlayerCharacter::Input_Ability4(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability4);
	OnAbility4ActionUse();
}

void ADPlayerCharacter::Input_Ability5(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability5);
	OnAbility5ActionUse();
}

void ADPlayerCharacter::Input_Ability6(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability6);
	OnAbility6ActionUse();
}

void ADPlayerCharacter::Input_Ability7(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Ability7);
	OnAbility7ActionUse();
}

void ADPlayerCharacter::Input_Pause(const FInputActionValue& InputActionValue)
{
	ADPlayerController* PlayerController = Cast<ADPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->TogglePlayerStats();
	}
	OnPauseActionUse();
}

void ADPlayerCharacter::Input_Interact(const FInputActionValue& InputActionValue)
{
	SendLocalInputToASC(true, EDAbilityInputID::Interact);
	OnInteractActionUse();
}

void ADPlayerCharacter::SetOverlappingWeapon(ADWeaponBase* Weapon)
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(false);
	}
	OverlappingWeapon = Weapon;
	if (IsLocallyControlled())
	{
		if (OverlappingWeapon)
		{
			OverlappingWeapon->ShowPickupWidget(true);
		}
	}
}

void ADPlayerCharacter::OnRep_OverlappingWeapon(ADWeaponBase* LastWeapon)
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(true);
	}
	if (LastWeapon)
	{
		LastWeapon->ShowPickupWidget(false);
	}
}

void ADPlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ADPlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

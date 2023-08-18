// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/DPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/DAbilitySystemComponent.h"
#include "GAS/DAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "PlayerController/DPlayerController.h"
#include "PlayerState/DPlayerState.h"
#include "UI/HUD/DHUD.h"
#include "Weapon/DWeaponBase.h"

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
	CameraBoom->TargetArmLength = 750.0f; // The camera follows at this distance behind the character
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	/*TurnRateGamepad = 45.f;*/

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	CombatComponent = CreateDefaultSubobject<UDCombatComponent>("CombatComponent");
	CombatComponent->SetIsReplicated(true);

	TraceSourceSocketName = "head";
}

void ADPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME_CONDITION_NOTIFY(ADPlayerCharacter,bInputDisabled,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION(ADPlayerCharacter, OverlappingWeapon, COND_OwnerOnly);
}

void ADPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CombatComponent)
	{
		CombatComponent->OwnerCharacter = this;
	}
}

FName ADPlayerCharacter::GetSocketNameTraceSource() const
{
	return TraceSourceSocketName;
}

void ADPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// This is for the Server, the same settings are set on OnRep_PlayerState for Clients in the DPlayerCharacter class
	InitializeASC();

	ADPlayerController* PC = Cast<ADPlayerController>(GetController());
	if (PC)
	{
		PC->CreateHUD();
	}
}

void ADPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// This is for the Client
	InitializeASC();
}

void ADPlayerCharacter::InitializeASC()
{
	ADPlayerState* DawnPlayerState = GetPlayerState<ADPlayerState>();
	if (DawnPlayerState)
	{
		AbilitySystemComponent = DawnPlayerState->GetAbilitySystemComponent();
		/* Make the Player State the owner actor and the player character the avatar actor */
		AbilitySystemComponent->InitAbilityActorInfo(DawnPlayerState,this);
		Cast<UDAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
		Attributes = DawnPlayerState->GetAttributeSetBase();
		AddCharacterAbilities(CharacterAbilities);

		if (ADPlayerController* DPlayerController = Cast<ADPlayerController>(GetController()))
		{
			if (ADHUD* DHUD = Cast<ADHUD>(DPlayerController->GetHUD()))
			{
				DHUD->InitOverlay(DPlayerController, DawnPlayerState, AbilitySystemComponent, Attributes);
			}
		}
		InitializePrimaryAttributes();
	}
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

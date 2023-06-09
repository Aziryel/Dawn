// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacterBase.h"

#include "DCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Dawn/GAS/DAbilitySystemComponent.h"
#include "Dawn/GAS/DAttributeSet.h"
#include "Dawn/PlayerController/DPlayerController.h"
#include "Dawn/PlayerState/DPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ADCharacterBase::ADCharacterBase(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UDCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	bAlwaysRelevant = true;

}

UAbilitySystemComponent* ADCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADCharacterBase, Attributes);
}

void ADCharacterBase::InitializeAttributes()
{
	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}

	if (!DefaultAttributes)
	{
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
}

bool ADCharacterBase::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void ADCharacterBase::SetHealth(float Health)
{
	return Attributes->SetHealth(Health);
}

void ADCharacterBase::SetMaxHealth(float MaxHealth)
{
	return Attributes->SetMaxHealth(MaxHealth);
}

void ADCharacterBase::SetMana(float Mana)
{
	return Attributes->SetMana(Mana);
}

void ADCharacterBase::SetMaxMana(float MaxMana)
{
	return Attributes->SetMaxMana(MaxMana);
}

void ADCharacterBase::SetStamina(float Stamina)
{
	return Attributes->SetStamina(Stamina);
}

void ADCharacterBase::SetMaxStamina(float MaxStamina)
{
	return Attributes->SetMaxStamina(MaxStamina);
}

void ADCharacterBase::SetMovementSpeed(float Speed) const
{
	if (Attributes)
	{
		return Attributes->SetMovementSpeed(Speed);
	}
}

float ADCharacterBase::GetHealth() const
{
	if (Attributes)
	{
		return Attributes->GetHealth();
	}
	return 0.0f;
}

float ADCharacterBase::GetMana() const
{
	if (Attributes)
	{
		return Attributes->GetMana();
	}
	return 0.0f;
}

float ADCharacterBase::GetStamina() const
{
	if (Attributes)
	{
		return Attributes->GetStamina();
	}
	return 0.0f;
}

float ADCharacterBase::GetMovementSpeed() const
{
	if (Attributes)
	{
		return Attributes->GetMovementSpeed();
	}
	return 0.0f;
}

float ADCharacterBase::GetAttackSpeed() const
{
	if (Attributes)
	{
		return Attributes->GetAttackSpeed();
	}
	return 0.0f;
}

// Called when the game starts or when spawned
void ADCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	 /*// This is for the Server, the same settings are set on OnRep_PlayerState for Clients in the DPlayerCharacter class
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
	}*/
}

void ADCharacterBase::AddCharacterAbilities(TArray<TSubclassOf<UDGameplayAbility>> AbilitiesToAdd)
{
	// Grant abilities but only on the server
	if (GetLocalRole() != ROLE_Authority || !IsValid(AbilitySystemComponent))
	{
		return;
	}

	for (TSubclassOf<UDGameplayAbility>& StartupAbility : AbilitiesToAdd)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
		UE_LOG(LogTemp, Warning, TEXT("Ability Name : %s"), *StartupAbility.GetDefaultObject()->GetName());
	}
}

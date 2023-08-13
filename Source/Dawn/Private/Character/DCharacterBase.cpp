// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/DCharacterBase.h"
#include "Abilities/Tasks/AbilityTask_NetworkSyncPoint.h"
#include "Character/DCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS/DAbilitySystemComponent.h"
#include "GAS/DAttributeSet.h"
#include "GAS/DGameplayAbility.h"
#include "Net/UnrealNetwork.h"

void ADCharacterBase::HighlightActor()
{
	UE_LOG(LogTemp, Warning, TEXT("Target Actor!!"));
}

void ADCharacterBase::UnHighlightActor()
{
	UE_LOG(LogTemp, Warning, TEXT("Untarget Actor!!"));
}

// Sets default values
ADCharacterBase::ADCharacterBase(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UDCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	bAlwaysRelevant = true;

}

bool ADCharacterBase::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	if (InteractionComponent == GetCapsuleComponent())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ADCharacterBase::GetPreInteractSyncType_Implementation(bool& bShouldSync, EAbilityTaskNetSyncType& Type,
	UPrimitiveComponent* InteractionComponent) const
{
	if (InteractionComponent == GetCapsuleComponent())
	{
		bShouldSync = false;
		Type = EAbilityTaskNetSyncType::OnlyClientWait;
	}
	else
	{
		bShouldSync = false;
		Type = EAbilityTaskNetSyncType::BothWait;
	}
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

// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/DCharacterBase.h"
#include "Abilities/Tasks/AbilityTask_NetworkSyncPoint.h"
#include "Character/DCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS/DAbilitySystemComponent.h"
#include "GAS/DAttributeSet.h"
#include "GAS/Abilities/DGameplayAbility.h"
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

void ADCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ADCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

bool ADCharacterBase::IsAlive() const
{
	return Attributes->GetHealth() > 0.0f;
}

// Called when the game starts or when spawned
void ADCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
}

FVector ADCharacterBase::GetCombatSocketLocation()
{
	return GetMesh()->GetSocketLocation(MagicSpawnSocketName);
}

void ADCharacterBase::AddCharacterAbilities()
{
	UDAbilitySystemComponent* DASC = CastChecked<UDAbilitySystemComponent>(AbilitySystemComponent);
	if (GetLocalRole() != ROLE_Authority) return;

	DASC->AddCharacterAbilities(StartupAbilities);
}

void ADCharacterBase::InitializeASC()
{
}

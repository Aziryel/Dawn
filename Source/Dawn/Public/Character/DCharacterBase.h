// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GAS/DAbilitySystemComponent.h"
#include "GAS/Abilities/DGameplayAbility.h"
#include "Interfaces/DInteractable.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"
#include "DCharacterBase.generated.h"

class ADWeaponBase;
class UDAttributeSet;
class UGameplayAbility;
class UAnimMontage;

UCLASS()
class DAWN_API ADCharacterBase : public ACharacter, public IAbilitySystemInterface, public IDInteractable, public ICombatInterface
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// Implements the abstract classes from IDInteractable
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	
	// Sets default values for this character's properties
	ADCharacterBase(const class FObjectInitializer& ObjectInitializer);
	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const override;
	virtual void GetPreInteractSyncType_Implementation(bool& bShouldSync, EAbilityTaskNetSyncType& Type, UPrimitiveComponent* InteractionComponent) const override;

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UDAttributeSet* GetAttributeSet() const { return Attributes; }

	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die() override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();

	UFUNCTION(BlueprintCallable, Category = "GAS")
	virtual bool IsAlive() const;

protected:
	virtual void BeginPlay() override;

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName MagicSpawnSocketName;

	virtual FVector GetCombatSocketLocation() override;

	// Ability System Component and Attributes are constructed in the PlayerState for the player and in the constructor for the enemies
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Ability System Component")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	// Ability System Component and Attributes are constructed in the PlayerState for the player and in the constructor for the enemies
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Ability System Component", Replicated)
	TObjectPtr<UDAttributeSet> Attributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	virtual void InitializeDefaultAttributes() const;
	
	/* Functions to Add */
	UFUNCTION()
	void AddCharacterAbilities();

	virtual void InitializeASC();

private:
	UPROPERTY(EditAnywhere, Category = "GAS|Default Gameplay Settings")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
	
};

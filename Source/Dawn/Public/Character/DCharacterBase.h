// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GAS/DAbilitySystemComponent.h"
#include "GAS/DGameplayAbility.h"
#include "Interfaces/DInteractable.h"
#include "GameFramework/Character.h"
#include "DCharacterBase.generated.h"

class ADWeaponBase;
class UDAttributeSet;

UCLASS()
class DAWN_API ADCharacterBase : public ACharacter, public IAbilitySystemInterface, public IDInteractable
{
	GENERATED_BODY()

public:
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
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GAS|Default Gameplay Settings")
	TArray<TSubclassOf<UDGameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GAS|Default Gameplay Settings")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	virtual void InitializeAttributes();

	UFUNCTION(BlueprintCallable, Category = "GAS")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	virtual void SetHealth(float Health);
	UFUNCTION(BlueprintCallable)
	virtual void SetMaxHealth(float MaxHealth);
	UFUNCTION(BlueprintCallable)
	virtual void SetMana(float Mana);
	UFUNCTION(BlueprintCallable)
	virtual void SetMaxMana(float MaxMana);
	UFUNCTION(BlueprintCallable)
	virtual void SetStamina(float Stamina);
	UFUNCTION(BlueprintCallable)
	virtual void SetMaxStamina(float MaxStamina);
	UFUNCTION(BlueprintCallable, Category = "GAS")
	void SetMovementSpeed(float Speed) const;

	UFUNCTION(BlueprintCallable, Category = "GAS")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "GAS")
	float GetMana() const;
	UFUNCTION(BlueprintCallable, Category = "GAS")
	float GetStamina() const;
	UFUNCTION(BlueprintCallable, Category = "GAS")
	float GetMovementSpeed() const;
	UFUNCTION(BlueprintCallable, Category = "GAS")
	float GetAttackSpeed() const;

protected:
	virtual void BeginPlay() override;

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

	// Ability System Component and Attributes are constructed in the PlayerState for the player and in the constructor for the enemies
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Ability System Component")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	// Ability System Component and Attributes are constructed in the PlayerState for the player and in the constructor for the enemies
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Ability System Component", Replicated)
	TObjectPtr<UDAttributeSet> Attributes;
	
	/* Functions to Add */
	UFUNCTION()
	void AddCharacterAbilities(TArray<TSubclassOf<UDGameplayAbility>> AbilitiesToAdd);
	
};

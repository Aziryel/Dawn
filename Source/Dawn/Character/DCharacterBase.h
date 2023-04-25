// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Dawn/GAS/DAbilitySystemComponent.h"
#include "Dawn/GAS/DGameplayAbility.h"
#include "Dawn/Input/DInputConfig.h"
#include "GameFramework/Character.h"
#include "DCharacterBase.generated.h"

UCLASS()
class DAWN_API ADCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADCharacterBase(const class FObjectInitializer& ObjectInitializer);

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Ability System Component")
	UDAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Ability System Component", Replicated)
	class UDAttributeSet* Attributes;
	
	/* Functions to Add */
	UFUNCTION()
	void AddCharacterAbilities(TArray<TSubclassOf<UDGameplayAbility>> AbilitiesToAdd);
	
};

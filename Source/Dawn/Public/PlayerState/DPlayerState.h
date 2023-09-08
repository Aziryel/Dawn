// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GAS/DAbilitySystemComponent.h"
#include "GAS/DAttributeSet.h"
#include "GameFramework/PlayerState.h"
#include "DPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DAWN_API ADPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ADPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UDAttributeSet* GetAttributeSetBase() const;

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }

	UPROPERTY(BlueprintReadWrite)
	FGameplayAbilityTargetDataHandle CurrentTracedTarget;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Ability System Component")
	TObjectPtr<UDAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Ability System Component")
	TObjectPtr<UDAttributeSet> AttributeSet;

private:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
};

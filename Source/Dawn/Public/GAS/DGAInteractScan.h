// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "Abilities/DGameplayAbility.h"
#include "DGAInteractScan.generated.h"

class UAbilityTask_WaitGameplayTagRemoved;
class UAbilityTask_WaitInputRelease;
class UDAT_WaitInteractableTarget;
class UAbilityTask_WaitInputPress;
class ADPlayerCharacter;

UCLASS()
class DAWN_API UDGAInteractScan : public UDGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void WaitForConfirmation();

	UFUNCTION(BlueprintCallable)
	void LoseInteractTarget();

	UFUNCTION()
	void AfterInputPress(float TimeWaited);

	UPROPERTY()
	UAbilityTask_WaitInputPress* WaitInputPress;
	
	UPROPERTY(BlueprintReadWrite, Category = "Interact")
	FGameplayAbilityTargetDataHandle CurrentTracedTarget;

	UPROPERTY(BlueprintReadWrite, Category = "Interact")
	UDAT_WaitInteractableTarget* WaitInteractableTarget;

	UPROPERTY(BlueprintReadWrite, Category = "Interact")
	UAbilityTask_WaitInputPress*  Task_WaitInputPress;

	UPROPERTY(BlueprintReadWrite, Category = "Interact")
	UAbilityTask_WaitInputRelease* Task_WaitInputRelease;

	UPROPERTY(BlueprintReadWrite, Category = "Interact")
	UAbilityTask_WaitGameplayTagRemoved* Task_WaitGameplayTagRemoved;

	UPROPERTY(BlueprintReadWrite)
	FVector TraceEndLocation;

	UPROPERTY()
	ADPlayerCharacter* PlayerCharacter;
	
};

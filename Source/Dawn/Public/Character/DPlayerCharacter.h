// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCharacterBase.h"
#include "DPlayerCharacter.generated.h"

class UDCombatComponent;

UCLASS()
class DAWN_API ADPlayerCharacter : public ADCharacterBase
{
	GENERATED_BODY()

public:
	ADPlayerCharacter(const class FObjectInitializer& ObjectInitializer);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;
	// Client only
	virtual void OnRep_PlayerState() override;
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;
	
	/** Socket to start the trace to search for intractable targets */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dawn|Interactable")
	FName TraceSourceSocketName;

	UFUNCTION(BlueprintCallable, Category = "Dawn|Interactable")
	FName GetSocketNameTraceSource() const;


protected:

	virtual void BeginPlay() override;

public:	
	UCameraComponent* GetCameraComponent() const { return FollowCamera; }
	
	// Public Setters
	void SetOverlappingWeapon(ADWeaponBase* Weapon);

private:

	UPROPERTY(VisibleAnywhere)
	UDCombatComponent* CombatComponent;
	
	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	ADWeaponBase* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(ADWeaponBase* LastWeapon);

	void InitializeASC() override;
};

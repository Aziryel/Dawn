// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Dawn/GAS/DAbilitySystemComponent.h"
#include "Dawn/GAS/DGameplayAbility.h"
#include "GameFramework/Actor.h"
#include "DWeaponBase.generated.h"

class UCapsuleComponent;
class UWidgetComponent;

UCLASS()
class DAWN_API ADWeaponBase : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	ADWeaponBase();
	virtual void Tick(float DeltaTime) override;
	
	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void ShowPickupWidget(bool bShowWidget);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	FGameplayTag WeaponTag;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	UDAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "GAS|Abilities")
	TArray<TSubclassOf<UDGameplayAbility>> Abilities;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Abilities")
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	UCapsuleComponent* PickupArea;
	
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	UWidgetComponent* PickupWidget;
};

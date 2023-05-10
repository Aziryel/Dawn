// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DCombatComponent.generated.h"

class ADWeaponBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAWN_API UDCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	friend class ADPlayerCharacter;

	UFUNCTION()
	void EquipWeapon(ADWeaponBase* NewWeapon);

protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY()
	ADPlayerCharacter* OwnerCharacter;
	
	UPROPERTY()
	ADWeaponBase* EquippedWeapon;
		
};

// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_HealthRegeneration.generated.h"

/**
 * 
 */
UCLASS()
class DAWN_API UMMC_HealthRegeneration : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_HealthRegeneration();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	FGameplayEffectAttributeCaptureDefinition VitalityDef;
	
};

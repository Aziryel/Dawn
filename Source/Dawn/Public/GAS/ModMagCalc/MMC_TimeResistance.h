// Copyright Aziryel

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_TimeResistance.generated.h"

/**
 * 
 */
UCLASS()
class DAWN_API UMMC_TimeResistance : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_TimeResistance();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	FGameplayEffectAttributeCaptureDefinition HolyResDef;
	FGameplayEffectAttributeCaptureDefinition DarkResDef;
};

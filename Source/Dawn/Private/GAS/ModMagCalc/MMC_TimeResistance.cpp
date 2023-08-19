// Copyright Aziryel


#include "GAS/ModMagCalc/MMC_TimeResistance.h"

#include "GAS/DAttributeSet.h"
#include "Interfaces/CombatInterface.h"

UMMC_TimeResistance::UMMC_TimeResistance()
{
	HolyResDef.AttributeToCapture = UDAttributeSet::GetHolyResistanceAttribute();
	HolyResDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	HolyResDef.bSnapshot = false;

	DarkResDef.AttributeToCapture = UDAttributeSet::GetDarknessResistanceAttribute();
	DarkResDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	DarkResDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(HolyResDef);
	RelevantAttributesToCapture.Add(DarkResDef);
}

float UMMC_TimeResistance::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags frp, source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float HolyRes = 0.f;
	GetCapturedAttributeMagnitude(HolyResDef, Spec, EvaluationParameters, HolyRes);
	HolyRes = FMath::Max<float>(HolyRes, 0.f);

	float DarkRes = 0.f;
	GetCapturedAttributeMagnitude(DarkResDef, Spec, EvaluationParameters, DarkRes);
	DarkRes = FMath::Max<float>(DarkRes, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 0.2f * HolyRes + 0.2f * DarkRes + 0.001 * PlayerLevel;
}

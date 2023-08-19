// Copyright Aziryel


#include "GAS/ModMagCalc/MMC_MaxStamina.h"

#include "GAS/DAttributeSet.h"
#include "Interfaces/CombatInterface.h"

UMMC_MaxStamina::UMMC_MaxStamina()
{
	SpeedDef.AttributeToCapture = UDAttributeSet::GetSpeedAttribute();
	SpeedDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	SpeedDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(SpeedDef);
}

float UMMC_MaxStamina::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags frp, source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Speed = 0.f;
	GetCapturedAttributeMagnitude(SpeedDef, Spec, EvaluationParameters, Speed);
	Speed = FMath::Max<float>(Speed, 1.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 200.f + 10.f * Speed + 10.f * PlayerLevel;
}

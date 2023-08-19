// Copyright Aziryel


#include "GAS/ModMagCalc/MMC_MaxMana.h"

#include "GAS/DAttributeSet.h"
#include "Interfaces/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UDAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	WisdomDef.AttributeToCapture = UDAttributeSet::GetWisdomAttribute();
	WisdomDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	WisdomDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
	RelevantAttributesToCapture.Add(WisdomDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags frp, source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, Intelligence);
	Intelligence = FMath::Max<float>(Intelligence, 1.f);

	float Wisdom = 0.f;
	GetCapturedAttributeMagnitude(WisdomDef, Spec, EvaluationParameters, Wisdom);
	Wisdom = FMath::Max<float>(Wisdom, 1.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	if (Intelligence == 1.f && Wisdom == 1.f && PlayerLevel == 1.f)
	{
		return 50.f;
	}
	if (Intelligence == 1.f && Wisdom == 1.f && PlayerLevel > 1.f)
	{
		return 50.f + 5.f * PlayerLevel;
	}
	if (Intelligence > 1.f && Wisdom == 1.f && PlayerLevel > 1.f)
	{
		return 50.f + 2.f * Intelligence + 5.f * PlayerLevel;
	}
	if (Intelligence == 1.f && Wisdom > 1.f && PlayerLevel > 1.f)
	{
		return 50.f + 2.f * Wisdom + 5.f * PlayerLevel;
	}

	return 50.f + 2.f * Intelligence + 2.f * Wisdom + 5.f * PlayerLevel;
}

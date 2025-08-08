// Copyright Nicholas Reardon


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;
	
	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, Intelligence);
	Intelligence = FMath::Max<float>(Intelligence, 0.f);
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	
	// Calculate Max Mana based on Intelligence and Player Level
	// Base mana is 50, plus 2 per Intelligence, plus 1 per Player Level
	// This gives a base mana of 50, plus 2 per Intelligence, plus 1 per Player Level
	// Base mana is 50, plus 2.5 per Intelligence, plus 15 per Player Level
	// This gives a base mana of 50, plus 2.5 per Intelligence, plus 15 per Player Level
	// Example: Intelligence 10, Player Level 5 = 50 + (10 * 2.5) + (5 * 15) = 50 + 25 + 75 = 150
	return 50.f + (Intelligence * 2.5f) + 15.f * PlayerLevel;
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/DPlayerStatsWidget.h"
#include "GAS/DAttributeSet.h"
#include "PlayerState/DPlayerState.h"

UDPlayerStatsWidget::UDPlayerStatsWidget()
{
	SetIsFocusable(true);
}

bool UDPlayerStatsWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if(!IsValid(StrButton)) return false;
	StrButton->OnClicked.AddDynamic(this, &UDPlayerStatsWidget::ModifyStrength);
	if(!IsValid(DexButton)) return false;
	DexButton->OnClicked.AddDynamic(this, &UDPlayerStatsWidget::ModifyDexterity);
	if(!IsValid(VitButton)) return false;
	VitButton->OnClicked.AddDynamic(this, &UDPlayerStatsWidget::ModifyVitality);
	if(!IsValid(IntButton)) return false;
	IntButton->OnClicked.AddDynamic(this, &UDPlayerStatsWidget::ModifyIntelligence);
	if(!IsValid(WisButton)) return false;
	WisButton->OnClicked.AddDynamic(this, &UDPlayerStatsWidget::ModifyWisdom);

	return true;
}

void UDPlayerStatsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*ADPlayerState* PlayerState = Cast<ADPlayerState>(GetOwningPlayerState());
	if (PlayerState)
	{
		UDAbilitySystemComponent* ASC = Cast<UDAbilitySystemComponent>(PlayerState->GetAbilitySystemComponent());
		if (ASC)
		{
			TArray<FGameplayAttribute> Attributes;
			Attributes.Add(UDAttributeSet::GetHealthAttribute());
			Attributes.Add(UDAttributeSet::GetMaxHealthAttribute());
			Attributes.Add(UDAttributeSet::GetManaAttribute());
			Attributes.Add(UDAttributeSet::GetMaxManaAttribute());
			Attributes.Add(UDAttributeSet::GetStaminaAttribute());
			Attributes.Add(UDAttributeSet::GetMaxStaminaAttribute());
			Attributes.Add(UDAttributeSet::GetMovementSpeedAttribute());
			Attributes.Add(UDAttributeSet::GetAttackSpeedAttribute());
			Attributes.Add(UDAttributeSet::GetCritChanceAttribute());
			Attributes.Add(UDAttributeSet::GetComboCounterAttribute());
			Attributes.Add(UDAttributeSet::GetStrengthAttribute());
			Attributes.Add(UDAttributeSet::GetDexterityAttribute());
			Attributes.Add(UDAttributeSet::GetVitalityAttribute());
			Attributes.Add(UDAttributeSet::GetIntelligenceAttribute());
			Attributes.Add(UDAttributeSet::GetWisdomAttribute());
			Attributes.Add(UDAttributeSet::GetDevotionAttribute());
			Attributes.Add(UDAttributeSet::GetBlasphemyAttribute());
			Attributes.Add(UDAttributeSet::GetPhysicalPowerAttribute());
			Attributes.Add(UDAttributeSet::GetMagicalPowerAttribute());
			Attributes.Add(UDAttributeSet::GetArmorAttribute());
			Attributes.Add(UDAttributeSet::GetMagicResistanceAttribute());
			Attributes.Add(UDAttributeSet::GetFireResistanceAttribute());
			Attributes.Add(UDAttributeSet::GetColdResistanceAttribute());
			Attributes.Add(UDAttributeSet::GetLightningResistanceAttribute());
			Attributes.Add(UDAttributeSet::GetHolyResistanceAttribute());
			Attributes.Add(UDAttributeSet::GetDarknessResistanceAttribute());
			Attributes.Add(UDAttributeSet::GetTimeResistanceAttribute());
			Attributes.Add(UDAttributeSet::GetDraconiumAttribute());
			Attributes.Add(UDAttributeSet::GetTimeShardsAttribute());
			Attributes.Add(UDAttributeSet::GetAncientTimeShardsAttribute());
			
			
			UAsyncTaskAttributeChanged* TaskAttributeChanged = UAsyncTaskAttributeChanged::ListenForAttributesChange(ASC, Attributes);
		}
	}*/
}

void UDPlayerStatsWidget::UpdateText(UTextBlock* TextToModify, float NewValue)
{
	TextToModify->SetText(FText::FromString(FString::FromInt(NewValue)));
}

void UDPlayerStatsWidget::UpdateProgressBar(UProgressBar* BarToModify, float NewValue, float MaxValue)
{
	float BarPercentage = NewValue / MaxValue;
	BarPercentage = FMath::Clamp(BarPercentage, 0.0f, 1.0f);
	BarToModify->SetPercent(BarPercentage);
}

void UDPlayerStatsWidget::UpdateStats(URichTextBlock* TextToModify, float NewValue)
{
	TextToModify->SetText(FText::FromString(FString::FromInt(NewValue)));
}

void UDPlayerStatsWidget::ModifyStrength()
{
	ADPlayerState* PlayerState = Cast<ADPlayerState>(GetOwningPlayerState());
	if (PlayerState)
	{
		PlayerState->GetAttributeSetBase()->SetStrength(PlayerState->GetAttributeSetBase()->GetStrength() + 1);
	}
}

void UDPlayerStatsWidget::ModifyDexterity()
{
	ADPlayerState* PlayerState = Cast<ADPlayerState>(GetOwningPlayerState());
	if (PlayerState)
	{
		PlayerState->GetAttributeSetBase()->SetDexterity(PlayerState->GetAttributeSetBase()->GetDexterity() + 1);
	}
}

void UDPlayerStatsWidget::ModifyVitality()
{
	ADPlayerState* PlayerState = Cast<ADPlayerState>(GetOwningPlayerState());
	if (PlayerState)
	{
		PlayerState->GetAttributeSetBase()->SetVitality(PlayerState->GetAttributeSetBase()->GetVitality() + 1);
	}
}

void UDPlayerStatsWidget::ModifyIntelligence()
{
	ADPlayerState* PlayerState = Cast<ADPlayerState>(GetOwningPlayerState());
	if (PlayerState)
	{
		PlayerState->GetAttributeSetBase()->SetIntelligence(PlayerState->GetAttributeSetBase()->GetIntelligence() + 1);
	}
}

void UDPlayerStatsWidget::ModifyWisdom()
{
	ADPlayerState* PlayerState = Cast<ADPlayerState>(GetOwningPlayerState());
	if (PlayerState)
	{
		PlayerState->GetAttributeSetBase()->SetWisdom(PlayerState->GetAttributeSetBase()->GetWisdom() + 1);
	}
}

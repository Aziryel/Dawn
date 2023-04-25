// Fill out your copyright notice in the Description page of Project Settings.


#include "DAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Dawn/Character/DCharacterBase.h"
#include "Dawn/PlayerController/DPlayerController.h"
#include "Dawn/PlayerState/DPlayerState.h"
#include "Net/UnrealNetwork.h"

UDAttributeSet::UDAttributeSet()
{
}

void UDAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue,0,GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue,0,GetMaxMana());
	}
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0, GetMaxStamina());
	}
}

void UDAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (!OwningPlayerState)
	{
		OwningPlayerState = Cast<ADPlayerState>(GetOwningActor());
	}
	if (!PlayerController && OwningPlayerState)
	{
		PlayerController = Cast<ADPlayerController>(OwningPlayerState->GetPlayerController());
	}
	
	if (Attribute == GetHealthAttribute() || Attribute == GetMaxHealthAttribute())
	{
		if (OwningPlayerState)
		{
			if (PlayerController && PlayerController->UIPlayerStats)
			{
				PlayerController->UIPlayerStats->UpdateText(PlayerController->UIPlayerStats->HealthText, GetHealth());
				PlayerController->UIPlayerStats->UpdateProgressBar(PlayerController->UIPlayerStats->HealthBar, GetHealth(), GetMaxHealth());
			}
		}
	}
	if (Attribute == GetManaAttribute() || Attribute == GetMaxManaAttribute())
	{
		if (OwningPlayerState)
		{
			if (PlayerController && PlayerController->UIPlayerStats)
			{
				PlayerController->UIPlayerStats->UpdateText(PlayerController->UIPlayerStats->ManaText, GetMana());
				PlayerController->UIPlayerStats->UpdateProgressBar(PlayerController->UIPlayerStats->ManaBar, GetMana(), GetMaxMana());
			}
		}
	}
	//TODO: Stamina
	if (Attribute == GetStrengthAttribute())
	{
		if (OwningPlayerState)
		{
			if (PlayerController && PlayerController->UIPlayerStats)
			{
				PlayerController->UIPlayerStats->UpdateStats(PlayerController->UIPlayerStats->StrText, GetStrength());
			}
		}
	}
	if (Attribute == GetDexterityAttribute())
	{
		if (OwningPlayerState)
		{
			if (PlayerController && PlayerController->UIPlayerStats)
			{
				PlayerController->UIPlayerStats->UpdateStats(PlayerController->UIPlayerStats->DexText, GetDexterity());
			}
		}
	}
	if (Attribute == GetVitalityAttribute())
	{
		if (OwningPlayerState)
		{
			if (PlayerController && PlayerController->UIPlayerStats)
			{
				PlayerController->UIPlayerStats->UpdateStats(PlayerController->UIPlayerStats->VitText, GetVitality());
			}
		}
	}
	if (Attribute == GetIntelligenceAttribute())
	{
		if (OwningPlayerState)
		{
			if (PlayerController && PlayerController->UIPlayerStats)
			{
				PlayerController->UIPlayerStats->UpdateStats(PlayerController->UIPlayerStats->IntText, GetIntelligence());
			}
		}
	}
	if (Attribute == GetWisdomAttribute())
	{
		if (OwningPlayerState)
		{
			if (PlayerController && PlayerController->UIPlayerStats)
			{
				PlayerController->UIPlayerStats->UpdateStats(PlayerController->UIPlayerStats->WisText, GetWisdom());
			}
		}
	}
}

void UDAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	FGameplayTagContainer SpecAssetTags;
	Data.EffectSpec.GetAllAssetTags(SpecAssetTags);

	// Get the Target actor, which should be our owner
	AActor* TargetActor = nullptr;
	ADCharacterBase* TargetCharacter = nullptr;
	AController* TargetController = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetCharacter = Cast<ADCharacterBase>(TargetActor);
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
	}
	AActor* SourceActor = nullptr;
	AController* SourceController = nullptr;
	if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
	{
		SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
		SourceController = Source->AbilityActorInfo->PlayerController.Get();
		if (SourceController == nullptr && SourceActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(SourceActor))
			{
				SourceController = Pawn->GetController();
			}
		}
	}

	// TODO: ShowDamageNumber for the target receiving or healing damage

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}
}

void UDAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Stamina,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,MaxStamina,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,MovementSpeed,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,AttackSpeed,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,CritChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,ComboCounter,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Strength,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Dexterity,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Vitality,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Intelligence,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Wisdom,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Devotion,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Blasphemy,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,PlayerLevel,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,PhysicalPower,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,MagicalPower,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Armor,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,MagicResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,FireResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,ColdResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,LightningResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,HolyResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,DarknessResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,TimeResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Draconium,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,TimeShards,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,AncientTimeShards,COND_None,REPNOTIFY_Always);
	
}

void UDAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Health,OldHealth);
}

void UDAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,MaxHealth,OldMaxHealth);
}

void UDAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Mana,OldMana);
}

void UDAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,MaxMana,OldMaxMana);
}

void UDAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Stamina,OldStamina);
}

void UDAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,MaxStamina,OldMaxStamina);
}

void UDAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,MovementSpeed,OldMovementSpeed);
}

void UDAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,AttackSpeed,OldAttackSpeed);
}

void UDAttributeSet::OnRep_CritChance(const FGameplayAttributeData& OldCritChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,CritChance,OldCritChance);
}

void UDAttributeSet::OnRep_ComboCounter(const FGameplayAttributeData& OldComboCounter)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,ComboCounter,OldComboCounter);
}

void UDAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Strength,OldStrength);
}

void UDAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Dexterity,OldDexterity);
}

void UDAttributeSet::OnRep_Vitality(const FGameplayAttributeData& OldVitality)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Vitality,OldVitality);
}

void UDAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Intelligence,OldIntelligence);
}

void UDAttributeSet::OnRep_Wisdom(const FGameplayAttributeData& OldWisdom)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Wisdom,OldWisdom);
}

void UDAttributeSet::OnRep_Devotion(const FGameplayAttributeData& OldDevotion)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Devotion,OldDevotion);
}

void UDAttributeSet::OnRep_Blasphemy(const FGameplayAttributeData& OldBlasphemy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Blasphemy,OldBlasphemy);
}

void UDAttributeSet::OnRep_PlayerLevel(const FGameplayAttributeData& OldPlayerLevel)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,PlayerLevel,OldPlayerLevel);
}

void UDAttributeSet::OnRep_PhysicalPower(const FGameplayAttributeData& OldPhysicalPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,PhysicalPower,OldPhysicalPower);
}

void UDAttributeSet::OnRep_MagicalPower(const FGameplayAttributeData& OldMagicalPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,MagicalPower,OldMagicalPower);
}

void UDAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Armor,OldArmor);
}

void UDAttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,MagicResistance,OldMagicResistance);
}

void UDAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,FireResistance,OldFireResistance);
}

void UDAttributeSet::OnRep_ColdResistance(const FGameplayAttributeData& OldColdResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,ColdResistance,OldColdResistance);
}

void UDAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,LightningResistance,OldLightningResistance);
}

void UDAttributeSet::OnRep_HolyResistance(const FGameplayAttributeData& OldHolyResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,HolyResistance,OldHolyResistance);
}

void UDAttributeSet::OnRep_DarknessResistance(const FGameplayAttributeData& OldDarknessResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,DarknessResistance,OldDarknessResistance);
}

void UDAttributeSet::OnRep_TimeResistance(const FGameplayAttributeData& OldTimeResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,TimeResistance,OldTimeResistance);
}

void UDAttributeSet::OnRep_Draconium(const FGameplayAttributeData& OldDraconium)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Draconium,OldDraconium);
}

void UDAttributeSet::OnRep_TimeShards(const FGameplayAttributeData& OldTimeShards)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,TimeShards,OldTimeShards);
}

void UDAttributeSet::OnRep_AncientTimeShards(const FGameplayAttributeData& OldAncientTimeShards)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,AncientTimeShards,OldAncientTimeShards);
}

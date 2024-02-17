// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/DAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "Character/DCharacterBase.h"
#include "Net/UnrealNetwork.h"
#include "PlayerState/DPlayerState.h"

UDAttributeSet::UDAttributeSet()
{
	const FDGameplayTags& GameplayTags = FDGameplayTags::Get();

	
	/* Primary Attributes */
	TagsToAttributes.Add(GameplayTags.PrimaryAttributeTag_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.PrimaryAttributeTag_Dexterity, GetDexterityAttribute);
	TagsToAttributes.Add(GameplayTags.PrimaryAttributeTag_Vitality, GetVitalityAttribute);
	TagsToAttributes.Add(GameplayTags.PrimaryAttributeTag_Speed, GetSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.PrimaryAttributeTag_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.PrimaryAttributeTag_Wisdom, GetWisdomAttribute);
	TagsToAttributes.Add(GameplayTags.PrimaryAttributeTag_Luck, GetLuckAttribute);
	TagsToAttributes.Add(GameplayTags.PrimaryAttributeTag_Devotion, GetDevotionAttribute);
	TagsToAttributes.Add(GameplayTags.PrimaryAttributeTag_Blasphemy, GetBlasphemyAttribute);
	/* Secondary Attributes */
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_MaxMana, GetMaxManaAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_MaxStamina, GetMaxStaminaAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_MovementSpeed, GetMovementSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_AttackSpeed, GetAttackSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_CritChance, GetCritChanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_CritResistance, GetCritResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_CritDamage, GetCritDamageAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_PhysicalPower, GetPhysicalPowerAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_MagicalPower, GetMagicalPowerAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_HealingPower, GetHealingPowerAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_DivinePower, GetDivinePowerAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_BlasphemousPower, GetBlasphemousPowerAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_ItemDiscovery, GetItemDiscoveryAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_MagicResistance, GetMagicResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_FireResistance, GetFireResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_ColdResistance, GetColdResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_LightningResistance, GetLightningResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_HolyResistance, GetHolyResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_DarknessResistance, GetDarknessResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.SecondaryAttributeTag_TimeResistance, GetTimeResistanceAttribute);
	
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
	
}

void UDAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of the effect, Target = target of the effect (owner of this AS)

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceAbilitySystemComponent = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceAbilitySystemComponent) && Props.SourceAbilitySystemComponent->AbilityActorInfo.IsValid() && Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	
	// Get the Target actor, which should be our owner
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UDAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	
	// TODO: ShowDamageNumber for the target receiving or healing damage

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		UE_LOG(LogTemp, Warning, TEXT("Changed Health on %s, Health: %f"), *GetNameSafe(Props.TargetAvatarActor), GetHealth());
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}
}

void UDAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Stamina,COND_None,REPNOTIFY_Always);

	// Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Strength,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Dexterity,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Vitality,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Speed,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Intelligence,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Wisdom,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Luck,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Devotion,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Blasphemy,COND_None,REPNOTIFY_Always);
	
	// Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,MaxStamina,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,MovementSpeed,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,AttackSpeed,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,CritChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,ComboCounter,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,PhysicalPower,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,MagicalPower,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,HealingPower,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,DivinePower,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,BlasphemousPower,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Armor,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,HealthRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,ManaRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,BlockChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,CritResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,CritDamage,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,ArmorPenetration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,ItemDiscovery,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,MagicResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,FireResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,ColdResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,LightningResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,HolyResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,DarknessResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,TimeResistance,COND_None,REPNOTIFY_Always);

	// Currency Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,Draconium,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,TimeShards,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAttributeSet,AncientTimeShards,COND_None,REPNOTIFY_Always);
	
}

void UDAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Health,OldHealth);
}

void UDAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,MaxHealth,OldMaxHealth);
}

void UDAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Mana,OldMana);
}

void UDAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,MaxMana,OldMaxMana);
}

void UDAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Stamina,OldStamina);
}

void UDAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,MaxStamina,OldMaxStamina);
}

void UDAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,MovementSpeed,OldMovementSpeed);
}

void UDAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,AttackSpeed,OldAttackSpeed);
}

void UDAttributeSet::OnRep_CritChance(const FGameplayAttributeData& OldCritChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,CritChance,OldCritChance);
}

void UDAttributeSet::OnRep_ComboCounter(const FGameplayAttributeData& OldComboCounter) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,ComboCounter,OldComboCounter);
}

void UDAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Strength,OldStrength);
}

void UDAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Dexterity,OldDexterity);
}

void UDAttributeSet::OnRep_Vitality(const FGameplayAttributeData& OldVitality) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Vitality,OldVitality);
}

void UDAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Speed,OldSpeed);
}

void UDAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Intelligence,OldIntelligence);
}

void UDAttributeSet::OnRep_Wisdom(const FGameplayAttributeData& OldWisdom) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Wisdom,OldWisdom);
}

void UDAttributeSet::OnRep_Luck(const FGameplayAttributeData& OldLuck) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Luck,OldLuck);
}

void UDAttributeSet::OnRep_Devotion(const FGameplayAttributeData& OldDevotion) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Devotion,OldDevotion);
}

void UDAttributeSet::OnRep_Blasphemy(const FGameplayAttributeData& OldBlasphemy) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Blasphemy,OldBlasphemy);
}

void UDAttributeSet::OnRep_PhysicalPower(const FGameplayAttributeData& OldPhysicalPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,PhysicalPower,OldPhysicalPower);
}

void UDAttributeSet::OnRep_MagicalPower(const FGameplayAttributeData& OldMagicalPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,MagicalPower,OldMagicalPower);
}

void UDAttributeSet::OnRep_HealingPower(const FGameplayAttributeData& OldHealingPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,HealingPower,OldHealingPower);
}

void UDAttributeSet::OnRep_DivinePower(const FGameplayAttributeData& OldDivinePower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,DivinePower,OldDivinePower);
}

void UDAttributeSet::OnRep_BlasphemousPower(const FGameplayAttributeData& OldBlasphemousPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,BlasphemousPower,OldBlasphemousPower);
}

void UDAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Armor,OldArmor);
}

void UDAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,HealthRegeneration,OldHealthRegeneration);
}

void UDAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,ManaRegeneration,OldManaRegeneration);
}

void UDAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,BlockChance,OldBlockChance);
}

void UDAttributeSet::OnRep_CritResistance(const FGameplayAttributeData& OldCritResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,CritResistance,OldCritResistance);
}

void UDAttributeSet::OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,CritDamage,OldCritDamage);
}

void UDAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,ArmorPenetration,OldArmorPenetration);
}

void UDAttributeSet::OnRep_ItemDiscovery(const FGameplayAttributeData& OldItemDiscovery) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,ItemDiscovery,OldItemDiscovery);
}

void UDAttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,MagicResistance,OldMagicResistance);
}

void UDAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,FireResistance,OldFireResistance);
}

void UDAttributeSet::OnRep_ColdResistance(const FGameplayAttributeData& OldColdResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,ColdResistance,OldColdResistance);
}

void UDAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,LightningResistance,OldLightningResistance);
}

void UDAttributeSet::OnRep_HolyResistance(const FGameplayAttributeData& OldHolyResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,HolyResistance,OldHolyResistance);
}

void UDAttributeSet::OnRep_DarknessResistance(const FGameplayAttributeData& OldDarknessResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,DarknessResistance,OldDarknessResistance);
}

void UDAttributeSet::OnRep_TimeResistance(const FGameplayAttributeData& OldTimeResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,TimeResistance,OldTimeResistance);
}

void UDAttributeSet::OnRep_Draconium(const FGameplayAttributeData& OldDraconium) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Draconium,OldDraconium);
}

void UDAttributeSet::OnRep_TimeShards(const FGameplayAttributeData& OldTimeShards) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,TimeShards,OldTimeShards);
}

void UDAttributeSet::OnRep_AncientTimeShards(const FGameplayAttributeData& OldAncientTimeShards) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,AncientTimeShards,OldAncientTimeShards);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/DAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Character/DCharacterBase.h"
#include "Net/UnrealNetwork.h"
#include "PlayerState/DPlayerState.h"

UDAttributeSet::UDAttributeSet()
{
	InitHealth(1000.f);
	InitMaxHealth(1000.f);
	InitMana(100.f);
	InitMaxMana(100.f);
	InitStamina(1000.f);
	InitMaxStamina(1000.f); 
	InitMovementSpeed(500.f);
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

void UDAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Intelligence,OldIntelligence);
}

void UDAttributeSet::OnRep_Wisdom(const FGameplayAttributeData& OldWisdom) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Wisdom,OldWisdom);
}

void UDAttributeSet::OnRep_Devotion(const FGameplayAttributeData& OldDevotion) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Devotion,OldDevotion);
}

void UDAttributeSet::OnRep_Blasphemy(const FGameplayAttributeData& OldBlasphemy) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Blasphemy,OldBlasphemy);
}

void UDAttributeSet::OnRep_PlayerLevel(const FGameplayAttributeData& OldPlayerLevel) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,PlayerLevel,OldPlayerLevel);
}

void UDAttributeSet::OnRep_PhysicalPower(const FGameplayAttributeData& OldPhysicalPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,PhysicalPower,OldPhysicalPower);
}

void UDAttributeSet::OnRep_MagicalPower(const FGameplayAttributeData& OldMagicalPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,MagicalPower,OldMagicalPower);
}

void UDAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAttributeSet,Armor,OldArmor);
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

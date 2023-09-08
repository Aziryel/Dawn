// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameplayTags.h"
#include "GameplayTagsManager.h"
#include "Engine/EngineTypes.h"

FDGameplayTags FDGameplayTags::GameplayTags;

void FDGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(GameplayTagsManager);

	GameplayTagsManager.DoneAddingNativeTags();
}

void FDGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	//Input Tags
	AddTag(InputTag_Move, "InputTag.Move", "Move input.");
	AddTag(InputTag_Look_Mouse, "InputTag.Look.Mouse", "Look (mouse) input.");
	AddTag(InputTag_Look_Stick, "InputTag.Look.Stick", "Look (stick) input.");
	AddTag(InputTag_Jump, "InputTag.Jump", "Jump input.");
	AddTag(InputTag_Primary, "InputTag.Primary", "Primary input.");
	AddTag(InputTag_Secondary, "InputTag.Secondary", "Secondary input.");
	AddTag(InputTag_WeaponArt, "InputTag.WeaponArt", "Weapon Art input.");
	AddTag(InputTag_Ability1, "InputTag.Ability1", "General Ability input.");
	AddTag(InputTag_Ability2, "InputTag.Ability2", "General Ability input.");
	AddTag(InputTag_Ability3, "InputTag.Ability3", "General Ability input.");
	AddTag(InputTag_Ability4, "InputTag.Ability4", "General Ability input.");
	AddTag(InputTag_Ability5, "InputTag.Ability5", "General Ability input.");
	AddTag(InputTag_Ability6, "InputTag.Ability6", "General Ability input.");
	AddTag(InputTag_Ability7, "InputTag.Ability7", "General Ability input.");
	AddTag(InputTag_Pause, "InputTag.Pause", "Pause input.");
	AddTag(InputTag_Interact, "InputTag.Interact", "Input to interact with items.");
	AddTag(InputTag_LMB, "InputTag.LMB", "Input Tag for the RMB");
	AddTag(InputTag_RMB, "InputTag.RMB", "Input Tag for the LMB");
	AddTag(InputTag_1, "InputTag.1", "Input tag for Key 1");
	AddTag(InputTag_2, "InputTag.2", "Input tag for Key 2");
	AddTag(InputTag_3, "InputTag.3", "Input tag for Key 3");
	AddTag(InputTag_4, "InputTag.4", "Input tag for Key 4");
	AddTag(InputTag_5, "InputTag.5", "Input tag for Key 5");
	AddTag(InputTag_6, "InputTag.6", "Input tag for Key 6");
	AddTag(InputTag_7, "InputTag.7", "Input tag for Key 7");
	AddTag(InputTag_8, "InputTag.8", "Input tag for Key 8");
	AddTag(InputTag_9, "InputTag.9", "Input tag for Key 9");
	AddTag(InputTag_0, "InputTag.0", "Input tag for Key 0");
	//WeaponTags
	AddTag(WeaponTag_Initial, "WeaponTag.Initial", "Weapon is Initialized in the World");
	AddTag(WeaponTag_Equipped, "WeaponTag.Equipped", "Weapon is equipped");
	AddTag(WeaponTag_Dropped, "WeaponTag.Dropped", "Weapon is dropped by a character");
	//Equipped Tags
	AddTag(EquippedTag_Sword, "EquippedTag.Sword", "Tag to Equip a Sword Weapon Type");
	//Ability Tags
	AddTag(AbilityTag_Interaction, "Ability.Interaction", "Tag to activate the Interaction");
	AddTag(AbilityTag_InteractEnd, "Ability.InteractEnd", "Tag to end the interaction");
	AddTag(AbilityTag_BlocksInteraction, "Ability.BlocksInteraction", "Tag to block the Interactions");
	//Gameplay Event Tags
	AddTag(GameplayEventTag_FireBolt, "Event.Montage.FireBolt", "Tag to spawn a fireball.");
	//State Tags
	AddTag(StateTag_Dead, "State.Dead", "To indicate the character is dead");
	AddTag(StateTag_Interaction, "State.Interaction", "Tag to when the player is interacting");
	AddTag(StateTag_InteractionRemoval, "State.InteractionRemoval", "Tag to use when the Interaction has been completed/cancelled");
	//Vital Attributes Tags
	AddTag(VitalAttributesTag_Health, "Attributes.Vital.Health", "Amount of damage to take before death");
	AddTag(VitalAttributesTag_Mana, "Attributes.Vital.Mana", "Resource to cast spells");
	AddTag(VitalAttributesTag_Stamina, "Attributes.Vital.Stamina", "Limit for the resource to perform actions");
	//Primary Attributes Tags
	AddTag(PrimaryAttributeTag_Strength, "Attributes.Primary.Strength", "Increases physical damage");
	AddTag(PrimaryAttributeTag_Dexterity, "Attributes.Primary.Dexterity", "Increases physical ranged damage");
	AddTag(PrimaryAttributeTag_Vitality, "Attributes.Primary.Vitality", "Increases physical defense and max health");
	AddTag(PrimaryAttributeTag_Speed, "Attributes.Primary.Speed", "");
	AddTag(PrimaryAttributeTag_Intelligence, "Attributes.Primary.Intelligence", "Increases magical damage");
	AddTag(PrimaryAttributeTag_Wisdom, "Attributes.Primary.Wisdom", "Increases healing effects");
	AddTag(PrimaryAttributeTag_Luck, "Attributes.Primary.Luck", "");
	AddTag(PrimaryAttributeTag_Devotion, "Attributes.Primary.Devotion", "Increases holy damage");
	AddTag(PrimaryAttributeTag_Blasphemy, "Attributes.Primary.Blasphemy", "Increases dark damage");
	//Secondary Attributes Tags
	AddTag(SecondaryAttributeTag_MaxHealth, "Attributes.Secondary.MaxHealth", "Max Amount of damage to take before death");
	AddTag(SecondaryAttributeTag_MaxMana, "Attributes.Secondary.MaxMana", "Limit for the resource to cast spells");
	AddTag(SecondaryAttributeTag_MaxStamina, "Attributes.Secondary.MaxStamina", "Resource to perform actions");
	AddTag(SecondaryAttributeTag_MovementSpeed, "Attributes.Secondary.MovementSpeed", "");
	AddTag(SecondaryAttributeTag_AttackSpeed, "Attributes.Secondary.AttackSpeed", "");
	AddTag(SecondaryAttributeTag_PhysicalPower, "Attributes.Secondary.PhysicalPower", "");
	AddTag(SecondaryAttributeTag_MagicalPower, "Attributes.Secondary.MagicalPower", "");
	AddTag(SecondaryAttributeTag_HealingPower, "Attributes.Secondary.HealingPower", "");
	AddTag(SecondaryAttributeTag_DivinePower, "Attributes.Secondary.DivinePower", "");
	AddTag(SecondaryAttributeTag_BlasphemousPower, "Attributes.Secondary.BlasphemousPower", "");
	AddTag(SecondaryAttributeTag_Armor, "Attributes.Secondary.Armor", "");
	AddTag(SecondaryAttributeTag_HealthRegeneration, "Attributes.Secondary.HealthRegeneration", "");
	AddTag(SecondaryAttributeTag_ManaRegeneration, "Attributes.Secondary.ManaRegeneration", "");
	AddTag(SecondaryAttributeTag_BlockChance, "Attributes.Secondary.BlockChance", "");
	AddTag(SecondaryAttributeTag_CritResistance, "Attributes.Secondary.CritResistance", "");
	AddTag(SecondaryAttributeTag_CritDamage, "Attributes.Secondary.CritDamage", "");
	AddTag(SecondaryAttributeTag_CritChance, "Attributes.Secondary.CritChance", "");
	AddTag(SecondaryAttributeTag_ArmorPenetration, "Attributes.Secondary.ArmorPenetration", "");
	AddTag(SecondaryAttributeTag_ItemDiscovery, "Attributes.Secondary.ItemDiscovery", "");
	AddTag(SecondaryAttributeTag_MagicResistance, "Attributes.Secondary.MagicResistance", "");
	AddTag(SecondaryAttributeTag_FireResistance, "Attributes.Secondary.FireResistance", "");
	AddTag(SecondaryAttributeTag_ColdResistance, "Attributes.Secondary.ColdResistance", "");
	AddTag(SecondaryAttributeTag_LightningResistance, "Attributes.Secondary.LightningResistance", "");
	AddTag(SecondaryAttributeTag_HolyResistance, "Attributes.Secondary.HolyResistance", "");
	AddTag(SecondaryAttributeTag_DarknessResistance, "Attributes.Secondary.DarknessResistance", "");
	AddTag(SecondaryAttributeTag_TimeResistance, "Attributes.Secondary.TimeResistance", "");
	//Message Tags
	AddTag(MessageTag_HealthCrystal, "Message.HealthCrystal", "");
	AddTag(MessageTag_ManaCrystal, "Message.ManaCrystal", "");
}

void FDGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}

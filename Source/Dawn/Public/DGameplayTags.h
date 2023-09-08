#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;

/**
 * Dawn GameplayTags
 *
 * Singleton containing native GameplayTags
 */

struct FDGameplayTags
{
public:
	static const FDGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeTags();

	//Input Tags
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Look_Mouse;
	FGameplayTag InputTag_Look_Stick;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Primary;
	FGameplayTag InputTag_Secondary;
	FGameplayTag InputTag_WeaponArt;
	FGameplayTag InputTag_Ability1;
	FGameplayTag InputTag_Ability2;
	FGameplayTag InputTag_Ability3;
	FGameplayTag InputTag_Ability4;
	FGameplayTag InputTag_Ability5;
	FGameplayTag InputTag_Ability6;
	FGameplayTag InputTag_Ability7;
	FGameplayTag InputTag_Interact;
	FGameplayTag InputTag_Pause;
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_5;
	FGameplayTag InputTag_6;
	FGameplayTag InputTag_7;
	FGameplayTag InputTag_8;
	FGameplayTag InputTag_9;
	FGameplayTag InputTag_0;
	
	//Weapon Tags
	FGameplayTag WeaponTag_Initial;
	FGameplayTag WeaponTag_Equipped;
	FGameplayTag WeaponTag_Dropped;
	//Equipped Tags
	FGameplayTag EquippedTag_Sword;
	//Ability Tags
	FGameplayTag AbilityTag_Interaction;
	FGameplayTag AbilityTag_InteractEnd;
	FGameplayTag AbilityTag_BlocksInteraction;
	//Gameplay Events Tags
	FGameplayTag GameplayEventTag_FireBolt;
	//State Tags
	FGameplayTag StateTag_Dead;
	FGameplayTag StateTag_Interaction;
	FGameplayTag StateTag_InteractionRemoval;
	//Vital Attributes Tags
	FGameplayTag VitalAttributesTag_Health;
	FGameplayTag VitalAttributesTag_Mana;
	FGameplayTag VitalAttributesTag_Stamina;
	//Primary Attributes Tags
	FGameplayTag PrimaryAttributeTag_Strength;
	FGameplayTag PrimaryAttributeTag_Dexterity;
	FGameplayTag PrimaryAttributeTag_Vitality;
	FGameplayTag PrimaryAttributeTag_Speed;
	FGameplayTag PrimaryAttributeTag_Intelligence;
	FGameplayTag PrimaryAttributeTag_Wisdom;
	FGameplayTag PrimaryAttributeTag_Luck;
	FGameplayTag PrimaryAttributeTag_Devotion;
	FGameplayTag PrimaryAttributeTag_Blasphemy;
	//Secondary Attributes Tags
	FGameplayTag SecondaryAttributeTag_MaxHealth;
	FGameplayTag SecondaryAttributeTag_MaxMana;
	FGameplayTag SecondaryAttributeTag_MaxStamina;
	FGameplayTag SecondaryAttributeTag_MovementSpeed;
	FGameplayTag SecondaryAttributeTag_AttackSpeed;
	FGameplayTag SecondaryAttributeTag_CritChance;
	FGameplayTag SecondaryAttributeTag_ComboCounter;
	FGameplayTag SecondaryAttributeTag_PhysicalPower;
	FGameplayTag SecondaryAttributeTag_MagicalPower;
	FGameplayTag SecondaryAttributeTag_HealingPower;
	FGameplayTag SecondaryAttributeTag_DivinePower;
	FGameplayTag SecondaryAttributeTag_BlasphemousPower;
	FGameplayTag SecondaryAttributeTag_Armor;
	FGameplayTag SecondaryAttributeTag_HealthRegeneration;
	FGameplayTag SecondaryAttributeTag_ManaRegeneration;
	FGameplayTag SecondaryAttributeTag_BlockChance;
	FGameplayTag SecondaryAttributeTag_CritResistance;
	FGameplayTag SecondaryAttributeTag_CritDamage;
	FGameplayTag SecondaryAttributeTag_ArmorPenetration;
	FGameplayTag SecondaryAttributeTag_ItemDiscovery;
	FGameplayTag SecondaryAttributeTag_MagicResistance;
	FGameplayTag SecondaryAttributeTag_FireResistance;
	FGameplayTag SecondaryAttributeTag_ColdResistance;
	FGameplayTag SecondaryAttributeTag_LightningResistance;
	FGameplayTag SecondaryAttributeTag_HolyResistance;
	FGameplayTag SecondaryAttributeTag_DarknessResistance;
	FGameplayTag SecondaryAttributeTag_TimeResistance;
	//Message Tags
	FGameplayTag MessageTag_HealthCrystal;
	FGameplayTag MessageTag_ManaCrystal;

protected:

	// Registers all of the tags with the Gameplaytags Manager
	void AddAllTags(UGameplayTagsManager& Manager);

	//Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

	static FDGameplayTags GameplayTags;
};

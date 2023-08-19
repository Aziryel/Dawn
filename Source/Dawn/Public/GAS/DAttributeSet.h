// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "DAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceAbilitySystemComponent = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

UCLASS()
class DAWN_API UDAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UDAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	

	// **************************** //
	// ***** Vital Attributes ***** //
	// **************************** //
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Health);

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Mana);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Stamina);

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

	// ******************************************************** //
	// ************** Vital Attributes End ******************** //
	// ******************************************************** //

	// **************************** //
	// **** Primary Attributes **** //
	// **************************** //
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Stats", ReplicatedUsing= OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Strength);

	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Stats", ReplicatedUsing= OnRep_Dexterity)
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Dexterity);

	UFUNCTION()
	virtual void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Stats", ReplicatedUsing= OnRep_Vitality)
	FGameplayAttributeData Vitality;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Vitality);

	UFUNCTION()
	virtual void OnRep_Vitality(const FGameplayAttributeData& OldVitality) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Stats", ReplicatedUsing= OnRep_Speed)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Speed);

	UFUNCTION()
	virtual void OnRep_Speed(const FGameplayAttributeData& OldSpeed) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Stats", ReplicatedUsing= OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Intelligence);

	UFUNCTION()
	virtual void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Stats", ReplicatedUsing= OnRep_Wisdom)
	FGameplayAttributeData Wisdom;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Wisdom);

	UFUNCTION()
	virtual void OnRep_Wisdom(const FGameplayAttributeData& OldWisdom) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_Luck)
	FGameplayAttributeData Luck;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Luck);

	UFUNCTION()
	virtual void OnRep_Luck(const FGameplayAttributeData& OldLuck) const;

	// Attributes modified by extra points
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Stats", ReplicatedUsing= OnRep_Devotion)
	FGameplayAttributeData Devotion;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Devotion);

	UFUNCTION()
	virtual void OnRep_Devotion(const FGameplayAttributeData& OldDevotion) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Stats", ReplicatedUsing= OnRep_Blasphemy)
	FGameplayAttributeData Blasphemy;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Blasphemy);

	UFUNCTION()
	virtual void OnRep_Blasphemy(const FGameplayAttributeData& OldBlasphemy) const;

	// ******************************************************** //
	// ************* Primary Attributes End ******************* //
	// ******************************************************** //

	// **************************** //
	// *** Secondary Attributes *** //
	// **************************** //

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,MaxHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,MaxMana);
	
	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,MaxStamina);

	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Power", ReplicatedUsing= OnRep_PhysicalPower)
	FGameplayAttributeData PhysicalPower;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,PhysicalPower);

	UFUNCTION()
	virtual void OnRep_PhysicalPower(const FGameplayAttributeData& OldPhysicalPower) const;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Power", ReplicatedUsing= OnRep_MagicalPower)
	FGameplayAttributeData MagicalPower;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,MagicalPower);

	UFUNCTION()
	virtual void OnRep_MagicalPower(const FGameplayAttributeData& OldMagicalPower) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Power", ReplicatedUsing= OnRep_HealingPower)
	FGameplayAttributeData HealingPower;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,HealingPower);

	UFUNCTION()
	virtual void OnRep_HealingPower(const FGameplayAttributeData& OldHealingPower) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Power", ReplicatedUsing= OnRep_DivinePower)
	FGameplayAttributeData DivinePower;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,DivinePower);

	UFUNCTION()
	virtual void OnRep_DivinePower(const FGameplayAttributeData& OldDivinePower) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Power", ReplicatedUsing= OnRep_BlasphemousPower)
	FGameplayAttributeData BlasphemousPower;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,BlasphemousPower);

	UFUNCTION()
	virtual void OnRep_BlasphemousPower(const FGameplayAttributeData& OldBlasphemousPower) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Defense", ReplicatedUsing= OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Armor);

	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Defense", ReplicatedUsing= OnRep_HealthRegeneration)
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,HealthRegeneration);

	UFUNCTION()
	virtual void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Defense", ReplicatedUsing= OnRep_ManaRegeneration)
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,ManaRegeneration);

	UFUNCTION()
	virtual void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_MovementSpeed)
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,MovementSpeed);

	UFUNCTION()
	virtual void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const;
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_AttackSpeed)
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,AttackSpeed);

	UFUNCTION()
	virtual void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_BlockChance)
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,BlockChance);

	UFUNCTION()
	virtual void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_CritChance)
	FGameplayAttributeData CritChance;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,CritChance);

	UFUNCTION()
	virtual void OnRep_CritChance(const FGameplayAttributeData& OldCritChance) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_CritResistance)
	FGameplayAttributeData CritResistance;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,CritResistance);

	UFUNCTION()
	virtual void OnRep_CritResistance(const FGameplayAttributeData& OldCritResistance) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_CritDamage)
	FGameplayAttributeData CritDamage;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,CritDamage);

	UFUNCTION()
	virtual void OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,ArmorPenetration);

	UFUNCTION()
	virtual void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_ItemDiscovery)
	FGameplayAttributeData ItemDiscovery;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,ItemDiscovery);

	UFUNCTION()
	virtual void OnRep_ItemDiscovery(const FGameplayAttributeData& OldItemDiscovery) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes", ReplicatedUsing= OnRep_ComboCounter)
	FGameplayAttributeData ComboCounter;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,ComboCounter);

	UFUNCTION()
	virtual void OnRep_ComboCounter(const FGameplayAttributeData& OldComboCounter) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Defense", ReplicatedUsing= OnRep_MagicResistance)
	FGameplayAttributeData MagicResistance;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,MagicResistance);

	UFUNCTION()
	virtual void OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Defense", ReplicatedUsing= OnRep_FireResistance)
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,FireResistance);

	UFUNCTION()
	virtual void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Defense", ReplicatedUsing= OnRep_ColdResistance)
	FGameplayAttributeData ColdResistance;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,ColdResistance);

	UFUNCTION()
	virtual void OnRep_ColdResistance(const FGameplayAttributeData& OldColdResistance) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Defense", ReplicatedUsing= OnRep_LightningResistance)
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,LightningResistance);

	UFUNCTION()
	virtual void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Defense", ReplicatedUsing= OnRep_HolyResistance)
	FGameplayAttributeData HolyResistance;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,HolyResistance);

	UFUNCTION()
	virtual void OnRep_HolyResistance(const FGameplayAttributeData& OldHolyResistance) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Defense", ReplicatedUsing= OnRep_DarknessResistance)
	FGameplayAttributeData DarknessResistance;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,DarknessResistance);

	UFUNCTION()
	virtual void OnRep_DarknessResistance(const FGameplayAttributeData& OldDarknessResistance) const;

	UPROPERTY(BlueprintReadOnly, Category="Attributes|Defense", ReplicatedUsing= OnRep_TimeResistance)
	FGameplayAttributeData TimeResistance;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,TimeResistance);

	UFUNCTION()
	virtual void OnRep_TimeResistance(const FGameplayAttributeData& OldTimeResistance) const;
	
	// ******************************************************** //
	// *********** Secondary Attributes End ******************* //
	// ******************************************************** //

	// **************************** //
	// *** Different currencies *** //
	// **************************** //
	
	// Currency to buy things from NPCs
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Expendables", ReplicatedUsing= OnRep_Draconium)
	FGameplayAttributeData Draconium;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,Draconium);

	UFUNCTION()
	virtual void OnRep_Draconium(const FGameplayAttributeData& OldDraconium) const;

	// The normal experience for leveling up and unlock places
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Expendables", ReplicatedUsing= OnRep_TimeShards)
	FGameplayAttributeData TimeShards;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,TimeShards);

	UFUNCTION()
	virtual void OnRep_TimeShards(const FGameplayAttributeData& OldTimeShards) const;

	// Rare experience to level up blasphemy and devotion and to unlock ancient grounds
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Expendables", ReplicatedUsing= OnRep_AncientTimeShards)
	FGameplayAttributeData AncientTimeShards;
	ATTRIBUTE_ACCESSORS(UDAttributeSet,AncientTimeShards);

	UFUNCTION()
	virtual void OnRep_AncientTimeShards(const FGameplayAttributeData& OldAncientTimeShards) const;

	// ******************************************************** //
	// ***************** Currencies End *********************** //
	// ******************************************************** //

private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};

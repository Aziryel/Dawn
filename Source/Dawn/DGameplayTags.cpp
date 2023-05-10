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
	AddTag(WeaponTag_Initial, "WeaponTag.Initial", "Weapon is Initialized in the World");
	AddTag(WeaponTag_Equipped, "WeaponTag.Equipped", "Weapon is equipped");
	AddTag(WeaponTag_Dropped, "WeaponTag.Dropped", "Weapon is dropped by a character");
	AddTag(EquippedTag_Sword, "EquippedTag.Sword", "Tag to Equip a Sword Weapon Type");
	AddTag(AbilityTag_Interaction, "Ability.Interaction", "Tag to activate the Interaction");
	AddTag(AbilityTag_InteractEnd, "Ability.InteractEnd", "Tag to end the interaction");
	AddTag(AbilityTag_BlocksInteraction, "Ability.BlocksInteraction", "Tag to block the Interactions");
	AddTag(StateTag_Dead, "State.Dead", "To indicate the character is dead");
	AddTag(StateTag_Interaction, "State.Interaction", "Tag to when the player is interacting");
	AddTag(StateTag_InteractionRemoval, "State.InteractionRemoval", "Tag to use when the Interaction has been completed/cancelled");
}

void FDGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}

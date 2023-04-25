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
}

void FDGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}

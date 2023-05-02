#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;

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
	FGameplayTag WeaponTag_Initial;
	FGameplayTag WeaponTag_Equipped;
	FGameplayTag WeaponTag_Dropped;
	FGameplayTag EquippedTag_Sword;

protected:

	// Registers all of the tags with the Gameplaytags Manager
	void AddAllTags(UGameplayTagsManager& Manager);

	//Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

	static FDGameplayTags GameplayTags;
};

// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Dawn : ModuleRules
{
	public Dawn(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"EnhancedInput", 
			"CommonUI",
			"GameplayAbilities", 
			"GameplayTags", 
			"GameplayTasks"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[] {
			"NavigationSystem", 
			"Niagara"
		});
	}
}

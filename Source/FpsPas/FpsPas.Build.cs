// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class FpsPas : ModuleRules
{
	public FpsPas(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"AIModule",
			"Core",
			"CoreUObject",
			"Engine",
			"HeadMountedDisplay",
			"InputCore",
			"NavigationSystem",
			"Niagara",
			"UMG",
			"UMGEditor"
		});
	}
}

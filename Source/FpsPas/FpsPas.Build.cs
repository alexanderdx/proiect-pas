// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class FpsPas : ModuleRules
{
	public FpsPas(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"HeadMountedDisplay",
			"InputCore",
			"Niagara",
			"UMG",
			"UMGEditor"
		});
	}
}

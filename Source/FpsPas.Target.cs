// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class FpsPasTarget : TargetRules
{
	public FpsPasTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		
		ExtraModuleNames.AddRange(new[]
		{
			"Animals",
			"FpsPas"
		});
	}
}

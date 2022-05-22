// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class FpsPasEditorTarget : TargetRules
{
	public FpsPasEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		
		ExtraModuleNames.AddRange(new[]
		{
			"Animals",
			"FpsPas"
		});
	}
}

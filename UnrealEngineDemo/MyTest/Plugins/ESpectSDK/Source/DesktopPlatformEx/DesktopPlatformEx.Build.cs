// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DesktopPlatformEx : ModuleRules
{
	public DesktopPlatformEx(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateIncludePaths.Add("DesktopPlatformEx/Private");

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"ApplicationCore",
				"Json",
			}
		);

	}
}

// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MagUs : ModuleRules
{
	public MagUs(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

        PrivateDependencyModuleNames.AddRange(new string[] { "LeapMotion" });
        PrivateIncludePathModuleNames.AddRange(new string[] { "LeapMotion" });
        PrivateIncludePaths.AddRange(new string[] { "LeapMotion/Public", "LeapMotion/Private" });
    }
}

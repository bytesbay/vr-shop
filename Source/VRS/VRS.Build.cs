// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class VRS : ModuleRules
{
	public VRS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Http", "Json", "JsonUtilities", "ProceduralMeshComponent", "UMG", "Slate", "SlateCore" });

		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            string PathToProject = "D:\\Documents\\Unreal Projects\\Noxel"; // изменить
            PublicIncludePaths.Add(Path.Combine(PathToProject, "Source\\Noxel\\include")); // изменить
            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";
            string LibrariesPath = Path.Combine(PathToProject, "Binaries", PlatformString);

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "assimp-vc140-mt.lib")); // изменить
        }
		else if(Target.Platform == UnrealTargetPlatform.Linux)
		{
			string PathToProject = "/home/bytesbay/Documents/Unreal Projects/VRS";
            PublicIncludePaths.Add(Path.Combine(PathToProject, "Source/VRS/include"));
            string LibrariesPath = Path.Combine(PathToProject, "Binaries", "Linux");

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libassimp.so"));
		}

	}
}

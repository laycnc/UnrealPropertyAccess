// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealPropertyAccess : ModuleRules
{
	public UnrealPropertyAccess(ReadOnlyTargetRules Target) : base(Target)
	{

		CppStandard = CppStandardVersion.Cpp17;

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}

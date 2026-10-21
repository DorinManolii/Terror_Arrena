// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Terror_Arrena : ModuleRules
{
	public Terror_Arrena(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"GameplayTags",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Terror_Arrena",
			"Terror_Arrena/Variant_Strategy",
			"Terror_Arrena/Variant_Strategy/UI",
			"Terror_Arrena/Variant_TwinStick",
			"Terror_Arrena/Variant_TwinStick/AI",
			"Terror_Arrena/Variant_TwinStick/Gameplay",
			"Terror_Arrena/Variant_TwinStick/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

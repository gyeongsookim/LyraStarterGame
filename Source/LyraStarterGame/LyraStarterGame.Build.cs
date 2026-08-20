// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LyraStarterGame : ModuleRules
{
	public LyraStarterGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"Test",
			"Temporary"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"LyraStarterGame",
			"LyraStarterGame/Variant_Platforming",
			"LyraStarterGame/Variant_Platforming/Animation",
			"LyraStarterGame/Variant_Combat",
			"LyraStarterGame/Variant_Combat/AI",
			"LyraStarterGame/Variant_Combat/Animation",
			"LyraStarterGame/Variant_Combat/Gameplay",
			"LyraStarterGame/Variant_Combat/Interfaces",
			"LyraStarterGame/Variant_Combat/UI",
			"LyraStarterGame/Variant_SideScrolling",
			"LyraStarterGame/Variant_SideScrolling/AI",
			"LyraStarterGame/Variant_SideScrolling/Gameplay",
			"LyraStarterGame/Variant_SideScrolling/Interfaces",
			"LyraStarterGame/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

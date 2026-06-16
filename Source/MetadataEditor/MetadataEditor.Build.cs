// Copyright (c) 2026 Mahyar Kazazi. All Rights Reserved.

using UnrealBuildTool;

public class MetadataEditor : ModuleRules
{
	public MetadataEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			[
				"Core",
				"CoreUObject",
				"Engine",
				"UMG",
				"UnrealEd",
				"Slate",
				"SlateCore",
				"Blutility"
			]
		);

		PrivateDependencyModuleNames.AddRange(
			[
			]
		);
	}
}

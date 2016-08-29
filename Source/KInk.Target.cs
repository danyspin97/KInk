// Copyright (c) 2016 WiseDragonStd

using UnrealBuildTool;
using System.Collections.Generic;

public class KInkTarget : TargetRules
{
	public KInkTarget(TargetInfo Target)
	{
		Type = TargetType.Game;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { "KInk" } );
	}
}

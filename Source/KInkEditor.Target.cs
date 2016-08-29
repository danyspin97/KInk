// Copyright (c) 2016 WiseDragonStd

using UnrealBuildTool;
using System.Collections.Generic;

public class KInkEditorTarget : TargetRules
{
	public KInkEditorTarget(TargetInfo Target)
	{
		Type = TargetType.Editor;
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

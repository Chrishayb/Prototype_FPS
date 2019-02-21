// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Prototype_NinjaPussEditorTarget : TargetRules
{
	public Prototype_NinjaPussEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Prototype_NinjaPuss" } );
	}
}

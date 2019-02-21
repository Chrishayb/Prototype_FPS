// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Prototype_NinjaPussTarget : TargetRules
{
	public Prototype_NinjaPussTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Prototype_NinjaPuss" } );
	}
}

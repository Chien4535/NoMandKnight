using UnrealBuildTool;

public class NoMandKnight2Target : TargetRules
{
	public NoMandKnight2Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("NoMandKnight2");
	}
}

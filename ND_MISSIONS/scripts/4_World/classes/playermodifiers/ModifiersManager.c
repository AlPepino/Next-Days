

// Script File
modded class ModifiersManager
{
	override void Init(){
		super.Init();
		AddModifier(new alpRadiationMdfr);
		AddModifier(new alpRadiationBlockMdfr);	
		
		AddModifier(new alpRadiationSick1Mdfr);
		AddModifier(new alpRadiationSick2Mdfr);
		AddModifier(new alpRadiationSick3Mdfr);
		AddModifier(new alpRadiationSick4Mdfr);
		AddModifier(new alpRadiationSick5Mdfr);
	}
}
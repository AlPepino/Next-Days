

// Script File
modded class ModifiersManager
{
	override void Init(){
		super.Init();
		AddModifier(new alpAnabolicMdfr);
		
		AddModifier(new alpTirednessMdfr);
		AddModifier(new alpSleepingMdfr);		
		AddModifier(new alpDrunkennessMdfr);	
		
		AddModifier(new BoneRegenMdfr); //check if is not added in default
		AddModifier(new BrokenArmsMdfr); //check if is not added in default		
		
		AddModifier(new alpImmunityInfluenzaMdfr);		
		
	}
}
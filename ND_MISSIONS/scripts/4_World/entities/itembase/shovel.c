modded class Shovel extends ItemBase
{

	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(alpActionDigInRadioactiveBarrel);
	}
}